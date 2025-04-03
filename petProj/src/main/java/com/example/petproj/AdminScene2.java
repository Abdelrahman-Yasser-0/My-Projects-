package com.example.petproj;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class AdminScene2 {
private Stage stage;
private Scene scene;
    @FXML
    private void handleAddPet(ActionEvent event) {
        try {
            FXMLLoader AddPetScene = new FXMLLoader(getClass().getResource("AddPet.fxml"));// define the root you want to switch to
            stage= (Stage) ((Node)event.getSource()).getScene().getWindow(); // handling the switch event
            scene = new Scene(AddPetScene.load()); // import the root to the scene
            stage.setScene(scene); // import the scene you want to show in the stage aka window bec the old scene holds the last root
            stage.show(); // show the stage

        } catch (IOException e) {
            System.err.println("Error loading AddPetScene: " + e.getMessage());
        }
    }

    @FXML
    private void handleRemovePet(ActionEvent event) {
        try {
            FXMLLoader AdminRequests = new FXMLLoader(getClass().getResource("RemovePet.fxml"));// define the root you want to switch to
            stage= (Stage) ((Node)event.getSource()).getScene().getWindow(); // handling the switch event
            scene = new Scene(AdminRequests.load()); // import the root to the scene
            stage.setScene(scene); // import the scene you want to show in the stage aka window bec the old scene holds the last root
            stage.show(); // show the stage
        } catch (IOException e) {
            System.err.println("Error loading RemovePetScene: " + e.getMessage());
        }
    }

    @FXML
    private void handleAdoptionRequest(ActionEvent event) {
        try {
            FXMLLoader AdminRequests = new FXMLLoader(getClass().getResource("PetRequest_Admin.fxml"));// define the root you want to switch to
            stage= (Stage) ((Node)event.getSource()).getScene().getWindow(); // handling the switch event
            scene = new Scene(AdminRequests.load()); // import the root to the scene
            stage.setScene(scene); // import the scene you want to show in the stage aka window bec the old scene holds the last root
            stage.show(); // show the stage

        } catch (IOException e) {
            System.err.println("Error loading Adoption Request of Admin Scene: " + e.getMessage());
        }
    }
}
