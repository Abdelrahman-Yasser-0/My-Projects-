package com.example.petproj;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import static com.example.petproj.LoginController.admin_id;
import static com.example.petproj.Petmanagement.pets;
import static com.example.petproj.PetRequest_Adopter_Controller.showNotification;

public class PetController implements Initializable {
    @FXML
   private TextField PetName;
    @FXML
    private TextField PetAge;
    @FXML
    private TextField PetBreed;
    @FXML
    private TextField PetHealth;
    @FXML
    private ComboBox <String> PetType;
    @FXML
    private Button submit,back;

    String petname;
    String petage;
    String petbreed;
    String pethealth;
    String pettype;

    private Stage stage;
    private Scene scene;
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        // add choices to combo box
        PetType.getItems().addAll("Cat", "Dog");
        // Set the submit button initially invisible
        submit.setVisible(false);

        // Add listeners to all text fields
        PetName.textProperty().addListener((observable, oldValue, newValue) -> checkAllFieldsFilled());
        PetAge.textProperty().addListener((observable, oldValue, newValue) -> checkAllFieldsFilled());
        PetBreed.textProperty().addListener((observable, oldValue, newValue) -> checkAllFieldsFilled());
        PetHealth.textProperty().addListener((observable, oldValue, newValue) -> checkAllFieldsFilled());
        PetType.valueProperty().addListener((observable, oldValue, newValue) -> checkAllFieldsFilled());

        // Set the action for the submit button
        submit.setOnAction(event -> submit(event));
        back.setOnAction(event -> Back(event));
    }
    @FXML
    private void Back(ActionEvent event) {
        // move to next scene
        try{ FXMLLoader Admin_Scene2 = new FXMLLoader(getClass().getResource("Admin_scene2.fxml"));// define the root you want to switch to
            stage= (Stage) ((Node)event.getSource()).getScene().getWindow(); // handling the switch event
            scene = new Scene(Admin_Scene2.load()); // import the root to the scene
            stage.setScene(scene); // import the scene you want to show in the stage aka window bec the old scene holds the last root
            stage.show(); // show the stage
        }catch (IOException e) {
            System.err.println("Error loading Admin Scene2 : " + e.getMessage());
        }
    }
public void submit (ActionEvent event){

    petname=PetName.getText();
    petage=PetAge.getText();
    petbreed=PetBreed.getText();
    pethealth=PetHealth.getText();
    pettype= PetType.getValue();
    boolean petFound=false;
    for(Pets p : pets){
        if( p.name.equals(petname)&&
            p.shelter_id==admin_id&&
            p.type.equals(pettype)) {
            petFound = true;
            break;}

    }
    if(petFound == false)
    {
        Petmanagement.addpet(Integer.toString(admin_id),petname,petbreed,petage,pethealth,pettype,false);
        showNotification("The Pet is Added Successfully");}
    else
        showNotification("The Pet Was Added Before");

    Back(event);

}


//      Checks if all text fields are filled and updates the visibility of the submit button.
    private void checkAllFieldsFilled() {
        boolean allFilled = !PetName.getText().trim().isEmpty() &&
                !PetAge.getText().trim().isEmpty() &&
                !PetBreed.getText().trim().isEmpty() &&
                !PetHealth.getText().trim().isEmpty() &&
                 PetType.getValue() != null;

        // Update the visibility of the submit button
        submit.setVisible(allFilled);
    }

}
