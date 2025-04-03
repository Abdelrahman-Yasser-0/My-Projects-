package com.example.petproj;

import javafx.animation.FadeTransition;
import javafx.animation.PauseTransition;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.io.IOException;
import java.net.URL;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ResourceBundle;
import java.util.stream.Collectors;

import static com.example.petproj.AdoptionManagement.addAdoption;
import static com.example.petproj.AdoptionManagement.adoptions;
import static com.example.petproj.LoginController.user_id;
import static com.example.petproj.LoginController.user_username;
import static com.example.petproj.Petmanagement.pets;
import static com.example.petproj.ShelterManagement.shelter;

public class PetRequest_Adopter_Controller implements Initializable {
    @FXML
    private Label Name, Breed, Age;

    @FXML
    private ComboBox<String> comboBox, Available_Shelter_Box, Available_Pets_Box;

    @FXML
    private TextField Pet_Name, Pet_Breed, Pet_Age;

    @FXML
    private ImageView imageView;

    @FXML
    private Button submit,back;
    Integer shelterId;
    int PetId;
    boolean Pet_wasRequested;
    private Stage stage;
    private Scene scene;
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        //hide all elements
        comboBox.setVisible(false);
        Available_Pets_Box.setVisible(false);
        set_visability(false);

        // add the available Shelter on the system to combo box
        Available_Shelter_Box.getItems().addAll(
                shelter.stream()
                        .map(shelter -> shelter.name) // Extract name from each shelter
                        .collect(Collectors.toList()) // Collect the mapped values into a List
        );
        Available_Shelter_Box.setOnAction(event -> handle_ShelterBox_Action(event));
        comboBox.setOnAction(event -> handle_ComboBox_Action(event));
        Available_Pets_Box.setOnAction(event -> handle_AvailablePetsBox_Action(event));
        submit.setOnAction(event -> submit(event));
        back.setOnAction(event -> Back(event));
    }
    @FXML
    private void Back(ActionEvent event) {
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
    @FXML
    private void submit(ActionEvent event) {

        boolean userExists =
                adoptions.stream().anyMatch(adoption ->
                                adoption.getPet().shelter_id==shelterId &&
                                adoption.getPet().breed.equals(Pet_Breed.getText() )&&
                                adoption.getPet().name.equals(Pet_Name.getText() )&&
                                adoption.getPet().age.equals(Pet_Age.getText() )&&
                                adoption.getAdopter().getName().equals(user_username) &&
                                Integer.toString(adoption.getAdopter().getID()).equals(Integer.toString(user_id)) &&
                                adoption.getStatus().equals("Pending") &&
                                adoption.get_Pet_type().equals(comboBox.getValue()));

        if(!userExists) {
            String currentDate = LocalDate.now().format(DateTimeFormatter.ofPattern("dd/MM/yyyy"));
            Adoption adoption= new Adoption(Integer.toString(PetId),Pet_Name.getText(),Pet_Breed.getText(),Pet_Age.getText(),user_username,Integer.toString(user_id),currentDate,"Pending",comboBox.getValue(),shelterId);
            addAdoption(adoption);

            pets.stream()
                    .filter(p -> p.id==PetId  )
                    .findFirst()
                    .ifPresent(pet -> {
                        pet.wasRequested=true;
                    });

        }
        Back(event);
    }
    @FXML
    private void handle_ShelterBox_Action(ActionEvent event) {
        // Hide all elements except the shelter box and the combo box
        set_visability(false);
        comboBox.setVisible(true);
        Available_Pets_Box.setVisible(false);
        comboBox.getItems().clear();
        comboBox.getItems().addAll("Cat", "Dog");

        // Find the selected shelter ID
        shelterId = shelter.stream()
                .filter(s -> s.name.equals(Available_Shelter_Box.getValue()))
                .map(Shelter::getId)
                .findFirst()
                .orElse(null);
    }

    @FXML
    private void handle_ComboBox_Action(ActionEvent event) {


        if (comboBox.getValue() != null) {
            // Hide all elements except the shelter box, combo box, and pets box
            set_visability(false);
            imageView.setVisible(true);
            Available_Pets_Box.setVisible(true);
            Available_Pets_Box.getItems().clear();

           //load images
            if(comboBox.getValue().equals("Cat"))
                loadPetImage("/images/cat.png");
            else loadPetImage("/images/dog.png");

            // Load pets for the selected shelter and type
            Available_Pets_Box.getItems().addAll(
                    pets.stream()
                            .filter(p -> p.shelter_id==shelterId && p.type.equals(comboBox.getValue()) && p.wasRequested== false)
                            .map(p -> p.name)
                            .collect(Collectors.toList())
            );
        }else imageView.setVisible(false);
    }

    @FXML
    private void handle_AvailablePetsBox_Action(ActionEvent event) {
        // Show all elements when a pet is selected
        if(comboBox.getValue() == null || Available_Pets_Box.getValue() == null)
        set_visability(false);
        else
            set_visability(true);

        // Populate text fields with selected pet details
        pets.stream()
                .filter(p -> p.name.equals(Available_Pets_Box.getValue()) &&  p.wasRequested== false )
                .findFirst()
                .ifPresent(pet -> {
                    Pet_Name.setText(pet.name);
                    Pet_Breed.setText(pet.breed);
                    Pet_Age.setText(pet.age);
                    PetId=pet.id;

                });
    }



    private void set_visability(boolean visable) {
        Name.setVisible(visable);
        Breed.setVisible(visable);
        Age.setVisible(visable);
        Pet_Name.setVisible(visable);
        Pet_Breed.setVisible(visable);
        Pet_Age.setVisible(visable);
        submit.setVisible(visable);

        if (!visable) {
            Pet_Name.clear();
            Pet_Breed.clear();
            Pet_Age.clear();
        }
    }
    private void loadPetImage(String imagePath) {
        try {
            Image image = new Image(getClass().getResource(imagePath).toExternalForm());
            imageView.setImage(image);
        } catch (NullPointerException e) {
            System.err.println("Image not found: " + imagePath);
            imageView.setImage(null);
        } catch (Exception e) {
            System.err.println("Unexpected error loading image: " + e.getMessage());
        }
    }

    // static notification method can use it in any class
    public static void showNotification(String content) {
        try {
            Stage notificationStage = new Stage();
            notificationStage.setTitle("Notification");

            Label notificationLabel = new Label(content);
            notificationLabel.setStyle("-fx-font-size: 16px; -fx-font-weight: bold; -fx-text-fill: black;");

            StackPane layout = new StackPane();
            layout.setStyle("-fx-background-color: #bbebff; -fx-padding: 20px;");
            layout.getChildren().add(notificationLabel);

            Scene notificationScene = new Scene(layout, 300, 150);
            notificationStage.setScene(notificationScene);

            FadeTransition fadeIn = new FadeTransition(Duration.seconds(1), layout);
            fadeIn.setFromValue(0.0);
            fadeIn.setToValue(1.0);
            fadeIn.play();

            notificationStage.show();

            PauseTransition pause = new PauseTransition(Duration.seconds(3));
            pause.setOnFinished(e -> {
                FadeTransition fadeOut = new FadeTransition(Duration.seconds(1), layout);
                fadeOut.setFromValue(1.0);
                fadeOut.setToValue(0.0);
                fadeOut.setOnFinished(event -> notificationStage.close());
                fadeOut.play();
            });
            pause.play();
        } catch (Exception e) {
            System.err.println("Error showing notification: " + e.getMessage());
        }
    }
}
