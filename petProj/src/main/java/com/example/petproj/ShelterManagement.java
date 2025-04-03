package com.example.petproj;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class ShelterManagement {
    public static ArrayList<Shelter> shelter = new ArrayList<Shelter>();
    private static final String shelterFilesPath = "./src/main/resources/files/";
    //ArrayList<Pets> pets
    public static void loadFilesData() {
        //  this.pets = pets;
        try(
                BufferedReader ShelterReader = new BufferedReader(new FileReader(shelterFilesPath + "shelter.txt")))

        {
            String line;
            while ((line = ShelterReader.readLine()) != null) {
                String[] singleShelterData = line.split(",");



                Shelter newShelter = new Shelter(singleShelterData[1], singleShelterData[2], singleShelterData[3]);
                shelter.add(newShelter);
            }
            ShelterReader.close();
        } catch(
                IOException error)

        {
            System.out.println(error.getMessage());
        }
    }
   // int shelter_id,
    public void addshelter( String name, String location, String contact_info) {

        Shelter newShelter = new Shelter( name,location, contact_info);
        shelter.add(newShelter);

    }
    public static void saveToFiles() {
        try(BufferedWriter shelterWriter = new BufferedWriter(new FileWriter(shelterFilesPath + "shelter.txt", false))) {
            for (Shelter shelter : shelter) {
                shelterWriter.write(shelter.toString());
                shelterWriter.newLine();
            }
            shelterWriter.close();
        } catch (IOException e) {
            System.out.println("Writing to shelter file failed");
        }


    }


    // FOR TESTING PURPOSES
    public void testPrintAllshelters() {
        System.out.println("Shelters Data : ");

        for (Shelter ad : shelter) {
            System.out.println(ad.toString());
        }
    }

    public static void searchForShelter(List<List<String>> available_Shelter_with_ID, List<String> available_Shelter_without_ID) {
        // Variable to track the current shelter index
        int indexshelter = 0;

        // Clear the lists to avoid duplicates if this method is called multiple times
        available_Shelter_with_ID.clear();
        available_Shelter_without_ID.clear();

        try {
            // Loop through each shelter object (assumes 'shelter' is a list of Shelter objects)
            for (Shelter ad : shelter) {
                // Ensure available_Shelter_with_ID has enough inner lists
                if (available_Shelter_with_ID.size() <= indexshelter) {
                    // Add a new empty list for the current shelter if it's missing
                    available_Shelter_with_ID.add(new ArrayList<String>());
                }

                // Add the shelter's name to the list that holds just the names (without ID)
                available_Shelter_without_ID.add(ad.name);

                // Add the shelter name and ID to the inner list in available_Shelter_with_ID
                // Index 0 will hold the shelter name, Index 1 will hold the shelter ID
                available_Shelter_with_ID.get(indexshelter).add(ad.name); // Adding name
                available_Shelter_with_ID.get(indexshelter).add(Integer.toString(ad.id)); // Adding ID

                // Increment the index for the next shelter
                indexshelter++;
            }
        } catch (NullPointerException e) {
            // Handle case where 'shelter' or any other object is null
            System.err.println("Error: NullPointerException occurred. Ensure that 'shelter' is not null.");
            e.printStackTrace();  // Print the stack trace for debugging
        } catch (IndexOutOfBoundsException e) {
            // Handle cases where the list index is out of bounds (though this should be avoided by the above checks)
            System.err.println("Error: IndexOutOfBoundsException occurred while accessing the shelter lists.");
            e.printStackTrace();
        } catch (Exception e) {
            // Catch any other unexpected exceptions
            System.err.println("An unexpected error occurred while processing shelters.");
            e.printStackTrace();
        }
    }



}



