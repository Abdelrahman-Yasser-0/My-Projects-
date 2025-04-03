package com.example.petproj;

import java.io.*;
import java.util.ArrayList;
import java.util.List;


public class AdoptionManagement {

    public static ArrayList<Adoption> adoptions = new ArrayList<Adoption>();


    // load adoption process from "adoption.txt"
    public static void loadFilesData(String AdoptionDataFileName) {
        // load admins
        try (BufferedReader adoptionReader = new BufferedReader(new FileReader("src/main/resources/files/" + AdoptionDataFileName))) {
            String line;
            while ((line = adoptionReader.readLine()) != null) {

                String[] singleAdoptionData = line.split(",");
                Adoption newAdoption = new Adoption(singleAdoptionData[1], singleAdoptionData[2], singleAdoptionData[3], singleAdoptionData[4], singleAdoptionData[5], singleAdoptionData[6], singleAdoptionData[7], singleAdoptionData[8],singleAdoptionData[9],Integer.parseInt(singleAdoptionData[10]));
                adoptions.add(newAdoption);


            }
            adoptionReader.close();
        } catch (IOException error) {
            System.out.println(error.getMessage());
        }
    }



    // save adoption process to "adoption.txt"
    public static void saveToFiles() {
        try(BufferedWriter adoptionWriter = new BufferedWriter(new FileWriter( "src/main/resources/files/Adoption.txt", false))) {
            for (Adoption adoption : adoptions) {
                adoptionWriter.write(adoption.toString());
                adoptionWriter.newLine();
            }
        } catch (IOException e) {
            System.out.println("Writing to Adoption file failed");
        }}

    public static void addAdoption(Adoption adoption) {
        adoptions.add(adoption);
    }


    public static void searchForAdoption(List<List<String>> available_Adoption, List<String> available_Adoption_name_only) {
        // Variable to track the current shelter index
        int indexAdoption = 0;

        // Clear the lists to avoid duplicates if this method is called multiple times
        available_Adoption.clear();
        available_Adoption_name_only.clear();

        try {
            // Loop through each shelter object (assumes 'adoptions' is a list of Adoption objects)
            for (Adoption ad : adoptions) {
                // Ensure available_Adoption has enough inner lists
                if (available_Adoption.size() <= indexAdoption) {
                    // Add a new empty list for the current Adoption if it's missing
                    available_Adoption.add(new ArrayList<String>());
                }

                // Add the pet's name to the list that holds just the names (without ID)
                available_Adoption_name_only.add(ad.getPet().name);

                // Add the Adoption name and ID to the inner list in available_Adoption
                // Index 0 will hold the Adoption name, Index 1 will hold the Adoption ID
                available_Adoption.get(indexAdoption).add(ad.getPet().name); // Adding pet name
                available_Adoption.get(indexAdoption).add(ad.getPet().breed); // Adding breed
                available_Adoption.get(indexAdoption).add(ad.getPet().age); // Adding age
                available_Adoption.get(indexAdoption).add(ad.getAdopter().name); // Adding Adopter name
                available_Adoption.get(indexAdoption).add(ad.getAdoptionDate()); // Adding Adoption date

                // Increment the index for the next Adoption
                indexAdoption++;
            }
        } catch (NullPointerException e) {
            // Handle case where 'Adoption' or any other object is null
            System.err.println("Error: NullPointerException occurred. Ensure that 'Adoption' is not null.");
            e.printStackTrace();  // Print the stack trace for debugging
        } catch (IndexOutOfBoundsException e) {
            // Handle cases where the list index is out of bounds (though this should be avoided by the above checks)
            System.err.println("Error: IndexOutOfBoundsException occurred while accessing the Adoption lists.");
            e.printStackTrace();
        } catch (Exception e) {
            // Catch any other unexpected exceptions
            System.err.println("An unexpected error occurred while processing Adoption.");
            e.printStackTrace();
        }
    }


}
