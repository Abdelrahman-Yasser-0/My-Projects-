package com.example.petproj;

import java.io.*;
import java.util.ArrayList;


public class UserManagement {
    public static ArrayList<Admin> admins = new ArrayList<Admin>();
    public static ArrayList<Adopter> adopters = new ArrayList<Adopter>();
    public static final String generalFilesPath ="./src/main/resources/files/";


    public static void loadFilesData(String adminsDataFileName, String adoptersDataFileName) {
        // load admins
        try(BufferedReader adminReader = new BufferedReader(new FileReader(generalFilesPath + adminsDataFileName))) {
            String line;
            while((line = adminReader.readLine() ) != null) {

                String [] singleAdminData = line.split(",");
                Admin newAdmin = new Admin(singleAdminData[1], singleAdminData[2], singleAdminData[3], singleAdminData[4], singleAdminData[5]);

                admins.add(newAdmin);
            }

            adminReader.close();
        } catch (IOException error) {
            System.out.println(error.getMessage());
        }


        // load adopters
        try(BufferedReader adopterReader = new BufferedReader(new FileReader(generalFilesPath + adoptersDataFileName))) {
            String line;
            while ((line = adopterReader.readLine()) != null) {
                String [] singleAdopterData = line.split(",");
                Adopter newAdopter = new Adopter(singleAdopterData[1], singleAdopterData[2], singleAdopterData[3], singleAdopterData[4], singleAdopterData[5]);
                adopters.add(newAdopter);
            }
            adopterReader.close();
        } catch (IOException error) {
            System.out.println(error.getMessage());
        }

    }

    // userType : admin or adopter
    // function return -1 in case of not user not found else it returns the index of the user in arrayList
   public static int searchForUser(String userName, String userType) {
        if (userType.equals("admin")) {
            for (Admin admin : admins) {
                if(admin.getUserName().equals(userName)) {
                    LoginController.admin_id=admin.getID();
                    return admins.indexOf(admin);
                }
            }
        } else if (userType.equals("adopter")) {
            for (Adopter adopter : adopters) {
                if(adopter.getUserName().equals(userName)) {
                    LoginController.user_id=adopter.getID();
                    return adopters.indexOf(adopter);

                }
            }
        }

        return -1;
   }








   // userType used to determine the type to which the given user data will be added to (admin or adopter)
   public static void addUser(String name, String userName, String password, String email, String phoneNum, String userType) {

            
       if(userType.equals("admin")) {
           Admin newAdmin = new Admin(name,userName, password, email, phoneNum);
           admins.add(newAdmin);
       } else if(userType.equals("adopter")) {
           Adopter newAdopter = new Adopter(name, userName, password, email, phoneNum);
           adopters.add(newAdopter);
       }
   }



    public static void saveToFiles() {
        try(BufferedWriter adminWriter = new BufferedWriter(new FileWriter(generalFilesPath + "admin.txt", false))) {
            for (Admin admin : admins) {
                adminWriter.write(admin.toString());
                adminWriter.newLine();
            }
        } catch (IOException e) {
            System.out.println("Writing to admin file failed");
        }

        try(BufferedWriter adopterWriter = new BufferedWriter(new FileWriter(generalFilesPath + "adopter.txt", false))) {
            for (Adopter adopter : adopters) {
                adopterWriter.write(adopter.toString());
                adopterWriter.newLine();
            }
        } catch (IOException e) {
            System.out.println("Writing to adopter file failed");
        }

    }
   

    // FOR TESTING PURPOSES
    public static void testPrintAllAdminsAndAdopters() {
        System.out.println("Admins Data : ");

        for (Admin ad : admins) {
            System.out.println(ad.toString());
        }


        System.out.println("Adopters Data : ");

        for (Adopter ad : adopters) {
            System.out.println(ad.toString());
        }
    }


}
