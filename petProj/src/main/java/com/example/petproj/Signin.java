package com.example.petproj;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import static com.example.petproj.LoginController.admin_id;
import static com.example.petproj.PetRequest_Adopter_Controller.showNotification;
import static com.example.petproj.Petmanagement.pets;
import static com.example.petproj.UserManagement.admins;
import static com.example.petproj.UserManagement.adopters;

public class Signin implements Initializable {


    @FXML
    private TextField name;
    @FXML
    private TextField username;
    @FXML
    private PasswordField password;
    @FXML
    private TextField email;
    @FXML
    private TextField phonenum;

    @FXML
    private ComboBox <String> role;

    @FXML
    private Button signin,back;

    String Name,Username,Password,Email,Phonenumber,Role;

    private String [] roletype = {"admin","adopter"};
    private Stage stage;
    private Scene scene;


    public void signin(ActionEvent event) {
    Name = name.getText();
    Username = username.getText();
    Password = password.getText();
    Email = email.getText();
    Phonenumber = phonenum.getText();
    Role = role.getValue();

    // Validate input fields
    if (!isValidEmail(Email)) {
        showNotification("Invalid email format.");
        return;
    }

    if (!isValidPhoneNumber(Phonenumber)) {
        showNotification("Phone number must be 11 digits.");
        return;
    }

        boolean userExists= role.equals("admin")
                ? admins.stream().anyMatch(admin ->
                        admin.getUserName().equals(Username)||
                        admin.getEmail().equals(Email) ||
                        admin.getPhoneNum().equals(Phonenumber))
                : adopters.stream().anyMatch(adopter ->
                        adopter.getUserName().equals(Username)||
                        adopter.getEmail().equals(Email) ||
                        adopter.getPhoneNum().equals(Phonenumber));

    if (!userExists) {
        UserManagement.addUser(Name, Username, Password, Email, Phonenumber, Role);
        showNotification("The account is created successfully!");
//        move to login scene
        Back(event);

    } else {
        showNotification("This account already exists.");
    }



    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        signin.setVisible(false);
        role.getItems().addAll(roletype);

        // Add listeners to all text fields
        name.textProperty().addListener((observable, oldValue, newValue) -> checkAllFieldsFilled());
        username.textProperty().addListener((observable, oldValue, newValue) -> checkAllFieldsFilled());
        password.textProperty().addListener((observable, oldValue, newValue) -> checkAllFieldsFilled());
        email.textProperty().addListener((observable, oldValue, newValue) -> checkAllFieldsFilled());
        phonenum.textProperty().addListener((observable, oldValue, newValue) -> checkAllFieldsFilled());
        role.valueProperty().addListener((observable, oldValue, newValue) -> checkAllFieldsFilled());

        // Set the action for the submit button
        signin.setOnAction(event -> signin(event));
        // Set the action for the submit button
        back.setOnAction(event -> Back(event));

    }

    @FXML
    private void Back(ActionEvent event) {

        try{
            FXMLLoader loginScene = new FXMLLoader(getClass().getResource("login.fxml"));// define the root you want to switch to
            stage= (Stage) ((Node)event.getSource()).getScene().getWindow(); // handling the switch event
            scene = new Scene(loginScene.load()); // import the root to the scene
            stage.setScene(scene); // import the scene you want to show in the stage aka window bec the old scene holds the last root
            stage.show(); // show the stage
        }catch (IOException e) {
            System.err.println("Error loading login scene : " + e.getMessage());
        }

    }

    //      Checks if all text fields are filled and updates the visibility of the submit button.
    private void checkAllFieldsFilled() {
        boolean allFilled = !name.getText().trim().isEmpty() &&
                !username.getText().trim().isEmpty() &&
                !password.getText().trim().isEmpty() &&
                !email.getText().trim().isEmpty() &&
                !phonenum.getText().trim().isEmpty() &&
                role.getValue() != null;

        // Update the visibility of the submit button
        signin.setVisible(allFilled);
    }
    private boolean isValidEmail(String email) {
        return email.matches("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$");
    }

    private boolean isValidPhoneNumber(String phone) {
        return phone.matches("^\\d{11}$");
    }

}
