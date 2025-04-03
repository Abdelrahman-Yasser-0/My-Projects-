package com.example.petproj;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.layout.VBox;

import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.stream.Collectors;

import static com.example.petproj.AdoptionManagement.adoptions;
import static com.example.petproj.LoginController.user_id;
import static com.example.petproj.ShelterManagement.shelter;

public class Notfication implements Initializable {
    ArrayList<Adoption> filterdnotfication = new ArrayList<>();
    @FXML
    private ListView<Adoption> notification ;

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
       filterdnotfication = (ArrayList<Adoption>) adoptions.stream() // filter the notification according to the id "must be unboxed bec of .collect(Collectors.toList()); creat a new type of list not arraylist
               .filter(adoption -> adoption.getAdopter().getID()==user_id)//search for a matched id
               .collect(Collectors.toList());//put it in a new list
        notification.getItems().addAll(filterdnotfication);// add the items of the id of the user to the listView

       /* notification.setCellFactory(parma-> new ListCell<>(){
        @Override
        protected void updateItem(Adoption notification, boolean empty) {
            super.updateItem(notification, empty);

            if (empty || notification == null) {
                setText(null);
                setGraphic(null);
            } else {
                VBox layout = new VBox(5);
                String shelterName = notification.getShelter() != null ? notification.getShelter().name : "Unknown Shelter";
                String petName = notification.getPet() != null ? notification.getPet().name : "Unknown Pet";
                String status = notification.getStatus() != null ? notification.getStatus() : "Unknown Status";

                Label titleLabel = new Label("Pet Adoption Response From: " + shelterName);
                Label messageLabel = new Label("Your Request For: " + petName + " is " + status);

                layout.getChildren().addAll(titleLabel, messageLabel);
                setGraphic(layout);
            }
        }
        });*/

        notification.setCellFactory(parma-> new ListCell<>(){
            @Override
            protected void updateItem(Adoption notification, boolean empty){
                super.updateItem(notification, empty);
                if (empty || notification == null) {
                    setText(null);
                    setGraphic(null);
                }
                else{
                    VBox layout = new VBox(5);
                    Label titleLabel = new Label("Pet Adoption Response From: " + shelter.get(notification.getPet().shelter_id).name); // Adoption.getShelter Returns null ????
                    Label messageLabel = new Label("Your Request For:"+notification.getPet().name+" Is "+notification.getStatus());
                    layout.getChildren().addAll(titleLabel, messageLabel);
                    setGraphic(layout);
                }
            }
        });
    }
}
