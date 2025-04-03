package com.example.petproj;

public class Admin extends User {
    private int ID;

    private String password;
    private static int adminCounter = 0;
    // should have a shelter variable to store managed shelter (to be implemented later)

    public Admin(String name, String userName, String password, String email, String phoneNum) {
        super(name, userName, email, phoneNum);
        adminCounter++;
        this.ID = adminCounter;
        this.password = password;


    }

    public int getID() {
        return ID;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    public String getPassword() {
        return password;
    }


    public String getPhoneNum() {
        if(phoneNum == null) {
            return "Admin has no Phone Num set";
        }
        return phoneNum;
    }



    public String getEmail() {
        if(email == null) {
            return "Admin has no Email set";
        }
        return email;
    }

    public static int getAdminCounter() {
        return adminCounter;
    }


    // NOTE : this will be the same order of data stored in text files
    @Override
    public String toString() {
        return ID + "," + name + "," + userName + "," + password + "," + email + "," + phoneNum;
    }
}
