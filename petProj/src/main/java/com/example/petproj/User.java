package com.example.petproj;

public abstract class User {


    public String name;
    public String userName;
    public String email;
    public String phoneNum;
    public User(){}
    public User(String name, String userName, String email, String phoneNum) {
        this.name = name;
        this.userName = userName;
        this.email = email;
        this.phoneNum = phoneNum;
    }

    public String getName() {
        return name;
    }

    public String getUserName() {
        return userName;
    }

    public abstract String getEmail();

    public abstract String getPhoneNum();

    public void setName(String name) {
        this.name = name;
    }
}
