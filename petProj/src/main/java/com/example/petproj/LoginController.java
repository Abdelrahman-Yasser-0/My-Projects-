package com.example.petproj;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.io.IOException;

import static com.example.petproj.PetRequest_Adopter_Controller.showNotification;


public class LoginController  {


    @FXML
    TextField adminusername,userusername;

    @FXML
    PasswordField adminpassword,userpassword;


    // new || this to handle the request
    public static String user_username;
    public static String admin_username;
    public static int user_id;
    public static int admin_id;

    private Stage stage;
    private Scene scene;

    String roletype;



    public void sginin(ActionEvent event) throws IOException {

//        try{
        FXMLLoader signin_page = new FXMLLoader(getClass().getResource("signin.fxml"));// define the root you want to switch to
        stage= (Stage) ((Node)event.getSource()).getScene().getWindow(); // handling the switch event
        scene = new Scene(signin_page.load()); // import the root to the scene
        stage.setScene(scene); // import the scene you want to show in the stage aka window bec the old scene holds the last root
        stage.show(); // show the stage
//    }catch (IOException e) {
//        System.err.println("Error loading Sign in Scene : " + e.getMessage());
//    }

    }


    public void adminlogin(ActionEvent event) throws IOException {

        roletype="admin";
        //admin login handling

        if(adminusername.getText().isEmpty() || adminpassword.getText().isEmpty()){
            if(adminusername.getText().isEmpty())
                showNotification("Pls Enter a Valid Username");


            if(adminpassword.getText().isEmpty())
                showNotification("Pls Enter a Valid Password");

        }
        else {


            if(UserManagement.searchForUser(adminusername.getText(),roletype)!=-1){
                admin_username = adminusername.getText();

                // show notification
                showNotification("Successful Login");

                //move to next scene
                try{
                FXMLLoader AdminScene2 = new FXMLLoader(getClass().getResource("Admin_scene2.fxml"));// define the root you want to switch to
                stage= (Stage) ((Node)event.getSource()).getScene().getWindow(); // handling the switch event
                scene = new Scene(AdminScene2.load()); // import the root to the scene
                stage.setScene(scene); // import the scene you want to show in the stage aka window bec the old scene holds the last root
                stage.show(); // show the stage
                }catch (IOException e) {
                    System.err.println("Error loading Admin_Scene2 : " + e.getMessage());
                }

            }
            else{
                showNotification("User Not Found");
            }
        }
    }

    public void userlogin(ActionEvent event) throws IOException {

        roletype="adopter";
        //user login handling

        if(userusername.getText().isEmpty() || userpassword.getText().isEmpty()){
            if(userusername.getText().isEmpty())
                showNotification("Pls Enter a Valid Username");


            if(userpassword.getText().isEmpty())
                showNotification("Pls Enter a Valid Password");

        }
        else {

            if(UserManagement.searchForUser(userusername.getText(),roletype)!=-1){
                user_username = userusername.getText();

                //show notification
                showNotification("Successful Login");

                // move to next scene
               try{ FXMLLoader Adopter_Scene2 = new FXMLLoader(getClass().getResource("Adopter_Scene2.fxml"));// define the root you want to switch to
                   stage= (Stage) ((Node)event.getSource()).getScene().getWindow(); // handling the switch event
                   scene = new Scene(Adopter_Scene2.load()); // import the root to the scene
                   stage.setScene(scene); // import the scene you want to show in the stage aka window bec the old scene holds the last root
                   stage.show(); // show the stage
                 }catch (IOException e) {
                System.err.println("Error loading Adopter Scene2 : " + e.getMessage());
            }

            }
            else{
                //show notification
                showNotification("User Not Found");
            }
        }
    }

}
