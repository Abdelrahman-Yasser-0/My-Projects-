package com.example.petproj;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;
import java.util.stream.Collectors;

import static com.example.petproj.AdoptionManagement.adoptions;
import static com.example.petproj.LoginController.admin_id;
import static com.example.petproj.PetRequest_Adopter_Controller.showNotification;
import static com.example.petproj.Petmanagement.pets;

public class PetRequest_Admin_Controller implements Initializable {

    @FXML
    private ComboBox<String> comboBox; // For selecting Cat or Dog
    @FXML
    private ComboBox<String> Available_Pets_Box; // For selecting a pet name
    @FXML
    private ImageView imageView; // To display pet image
    @FXML
    private Label Name, Age, Breed, adopter, Date, status;
    @FXML
    private TextField Pet_Name, Pet_Age, Pet_Breed, Pet_Adopter, Pet_Date, request_status;
    @FXML
    private Button accept, reject,back;



    private Stage stage;
    private Scene scene;
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        try {
            // Initially, only the comboBox for selecting Cat or Dog is visible
            setupVisibility(false);
            Available_Pets_Box.setVisible(false);
            // Populate the comboBox for Cat or Dog
            comboBox.getItems().addAll("Cat", "Dog");

            // Add a listener to the comboBox
            comboBox.setOnAction(event ->{handlePetTypeSelection();});

            // Add a listener to Available_Pets_Box
            Available_Pets_Box.setOnAction(event -> {handlePetNameSelection();});
            back.setOnAction(event ->Back(event));
        } catch (Exception e) {
            e.printStackTrace(); // Handle initialization error
        }

    }

    private void setupVisibility(boolean visible) {
        try {
            // Only comboBox is visible
            Name.setVisible(visible);
            Age.setVisible(visible);
            Breed.setVisible(visible);
            adopter.setVisible(visible);
            Date.setVisible(visible);
            status.setVisible(visible);
            Pet_Name.setVisible(visible);
            Pet_Age.setVisible(visible);
            Pet_Breed.setVisible(visible);
            Pet_Adopter.setVisible(visible);
            Pet_Date.setVisible(visible);
            request_status.setVisible(visible);
            accept.setVisible(visible);
            reject.setVisible(visible);
        } catch (Exception e) {
            e.printStackTrace(); // Handle visibility error
        }
    }

    private void handlePetTypeSelection() {
        Available_Pets_Box.setVisible(true);
        setupVisibility(false);

        if (comboBox.getValue() == null) return;

        // Show image based on selected pet type
        String imagePath = comboBox.getValue().equals("Cat")
                ? "images/cat.png"
                : "images/dog.png"; // Adjust the path as needed
        imageView.setImage(new Image(imagePath));

        // Show Available_Pets_Box and populate it based on selected pet type
        Available_Pets_Box.getItems().clear();
        Available_Pets_Box.getItems().addAll(
                adoptions.stream()
                        .filter(adoption -> adoption.getPet().type.equals(comboBox.getValue()) && adoption.getStatus().equals("Pending") && adoption.getPet().shelter_id==admin_id)
                        .map(adoption -> adoption.getPet().name)
                        .collect(Collectors.toList()));

    }

    private void handlePetNameSelection() {
        try {
            Available_Pets_Box.setVisible(true);
            setupVisibility(true);


            String selectedPetName = Available_Pets_Box.getValue();
            if (selectedPetName == null) return;

            // Find the selected pet in the list and display its details
            for (Adoption adoption : adoptions) {
                if (adoption.getPet().name.equalsIgnoreCase(selectedPetName) && adoption.get_Pet_type().equals(comboBox.getValue())) {
                    Pet_Name.setText(adoption.getPet().name);
                    Pet_Breed.setText(adoption.getPet().breed);
                    Pet_Age.setText(String.valueOf(adoption.getPet().age));
                    Pet_Adopter.setText(adoption.getAdopter().name);
                    Pet_Date.setText(adoption.getAdoptionDate());
                    request_status.setText(adoption.getStatus());

                    // Set the action for the Accept button
                    accept.setOnAction(event ->{
                        adoption.setStatus("Accepted");
                        Accept(event) ;});

                    // Set the action for the Reject button
                    reject.setOnAction(event -> {
                        adoption.setStatus("Rejected");
                        Reject(event) ;});
                    break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace(); // Handle pet name selection error
        }
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

    public void Accept(ActionEvent event) {

        showNotification("The Request is Accepted");

        Back(event);
    }
    public void Reject(ActionEvent event)  {
        showNotification("The Request is Rejected");

        pets.stream()
                .filter(p -> p.name.equals(Pet_Name.getText()))
                .findFirst()
                .ifPresent(pet -> {
                    pet.wasRequested=false;
                });

        Back(event);
    }
}
