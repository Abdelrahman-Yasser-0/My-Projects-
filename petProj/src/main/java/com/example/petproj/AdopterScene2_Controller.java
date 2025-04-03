package com.example.petproj;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;

import java.io.IOException;

public class AdopterScene2_Controller {
    private Stage stage;
    private Scene scene;
    @FXML
    private void handleMyOldRequests(ActionEvent event) {
        try {

            FXMLLoader AddPetScene = new FXMLLoader(getClass().getResource("MyOldRequests.fxml"));// define the root you want to switch to
            stage= (Stage) ((Node)event.getSource()).getScene().getWindow(); // handling the switch event
            scene = new Scene(AddPetScene.load()); // import the root to the scene
            stage.setScene(scene); // import the scene you want to show in the stage aka window bec the old scene holds the last root
            stage.show(); // show the stage

        } catch (IOException e) {
            System.err.println("Error Old Requests: " + e.getMessage());
        }
    }

    @FXML
    private void handleSendRequests(ActionEvent event) {
        try {
            FXMLLoader AdopterRequests = new FXMLLoader(getClass().getResource("PetRequest_Adopter.fxml"));// define the root you want to switch to
            stage= (Stage) ((Node)event.getSource()).getScene().getWindow(); // handling the switch event
            scene = new Scene(AdopterRequests.load()); // import the root to the scene
            stage.setScene(scene); // import the scene you want to show in the stage aka window bec the old scene holds the last root
            stage.show(); // show the stage
        } catch (IOException e) {
            System.err.println("Error loading Adoption Request of Adopter Scene: " + e.getMessage());
        }
    }

    @FXML
    private void NotficationView() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("Notification.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        Stage stage = new Stage();
        stage.setTitle("Notification");
        stage.setScene(scene);
        stage.show();
    }

}
