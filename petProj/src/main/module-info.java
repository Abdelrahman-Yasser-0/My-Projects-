module com.example.petproj {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.petproj to javafx.fxml;
    exports com.example.petproj;
}