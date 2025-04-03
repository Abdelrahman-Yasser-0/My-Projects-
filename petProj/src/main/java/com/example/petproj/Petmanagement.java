package com.example.petproj;
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;


public class Petmanagement {
    public static ArrayList<Pets> pets = new ArrayList<Pets>();
    private static final String petsFilesPath = "./src/main/resources/files/";

        public static void loadFilesData(){

        try (
                BufferedReader petReader = new BufferedReader(new FileReader(petsFilesPath + "pets.txt"))) {
            String line;
            while ((line = petReader.readLine()) != null) {
                String[] singlePetData = line.split(",");
                Pets newPets = new Pets(singlePetData[1], singlePetData[2], singlePetData[3], singlePetData[4], singlePetData[5],singlePetData[6],Boolean.parseBoolean(singlePetData[7]));
                pets.add(newPets);
            }
            petReader.close();
        } catch (IOException error) {
            System.out.println(error.getMessage());
        }
    }

    public static void addpet(String shelter_id, String name, String breed, String age, String health_status, String type,boolean wasRequested) {

        Pets newPet = new Pets(name, breed, age, health_status, type,shelter_id,wasRequested);
        pets.add(newPet);

    }


    public static void saveToFiles() {
        try (BufferedWriter petsWriter = new BufferedWriter(new FileWriter(petsFilesPath + "pets.txt", false))) {
            for (Pets pets : pets) {
                petsWriter.write(pets.toString());
                petsWriter.newLine();
            }
        } catch (IOException e) {
            System.out.println("Writing to pets file failed");
        }


    }


    // FOR TESTING PURPOSES
    public void testPrintAllpets() {
        System.out.println("Pets Data : ");

        for (Pets ad : pets) {
            System.out.println(ad.toString());
        }


    }


    public static void searchForPet(List<List<String>> availableCats, List<String> availableCats_name_only, List<List<String>> availableDogs, List<String> availableDogs_name_only, int shelter_id) {
        // Clear the lists before re-populating to avoid stale data
        availableCats.clear();
        availableDogs.clear();
        availableCats_name_only.clear();
        availableDogs_name_only.clear();

        // Indexes for Cats and Dogs in their respective lists
        int indexCat = 0;
        int indexDog = 0;

        // Loop through all the pets (both cats and dogs)
        for (Pets ad : pets) {
            // Check if the pet is a Cat and belongs to the selected shelter
            if ("Cat".equals(ad.type) && ad.shelter_id == shelter_id) {
                // Ensure enough space exists in availableCats
                if (indexCat >= availableCats.size()) {
                    availableCats.add(new ArrayList<>(Arrays.asList(ad.name, ad.breed, ad.age, Integer.toString(ad.id))));
                } else {
                    availableCats.get(indexCat).set(0, ad.name);  // Name
                    availableCats.get(indexCat).set(1, ad.breed); // Breed
                    availableCats.get(indexCat).set(2, ad.age);   // Age
                    availableCats.get(indexCat).set(3, Integer.toString(ad.id)); // ID
                }
                // Update the name-only list for cats
                availableCats_name_only.add(ad.name);
                indexCat++; // Move to the next index for cats

            } else if ("Dog".equals(ad.type) && ad.shelter_id == shelter_id) {
                // Ensure enough space exists in availableDogs
                if (indexDog >= availableDogs.size()) {
                    availableDogs.add(new ArrayList<>(Arrays.asList(ad.name, ad.breed, ad.age, Integer.toString(ad.id))));
                } else {
                    availableDogs.get(indexDog).set(0, ad.name);  // Name
                    availableDogs.get(indexDog).set(1, ad.breed); // Breed
                    availableDogs.get(indexDog).set(2, ad.age);   // Age
                    availableDogs.get(indexDog).set(3, Integer.toString(ad.id)); // ID
                }
                // Update the name-only list for dogs
                availableDogs_name_only.add(ad.name);
                indexDog++; // Move to the next index for dogs
            }
        }

    }






}



