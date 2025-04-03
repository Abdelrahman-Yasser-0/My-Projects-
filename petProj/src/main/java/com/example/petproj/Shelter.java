package com.example.petproj;

public class Shelter {
    public int id ;
    public String name ;
    public String location ;
    public String contact_info;
    private static int ShelterCounter = 0;
  //public Pets pets [] = new Pets[9];

    public Shelter( String name, String location, String contact_info) {
        ShelterCounter++;
        this.id = ShelterCounter;
        this.name = name;
        this.location = location;
        this.contact_info = contact_info;
    }

    public int getId() {
        return id;
    }

    @Override
    public String toString() {
        return id + "," + name + "," + location + "," + contact_info ;
    }
}