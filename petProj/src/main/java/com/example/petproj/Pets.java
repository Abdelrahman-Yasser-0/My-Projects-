package com.example.petproj;

public class Pets {
    public int shelter_id; //shouldnt be static
    public String type ;
    public int id;
    public String name;
    public String breed;
    private static int PetCounter = 0;
    public String age;
    public String health_status;
    public boolean wasRequested =false ;

    public Pets(){}
    public Pets( String name, String breed, String age, String health_status,String type, String shelter_id,boolean wasRequested) {


        PetCounter++;
        this.id = PetCounter;
        this.name = name;
        this.breed = breed;
        this.age = age;
        this.health_status = health_status;
        this.type = type;
        this.shelter_id=Integer.parseInt(shelter_id);
        this.wasRequested = wasRequested;
    }

    @Override
    public String toString() {
        return id + "," + name + "," + breed + "," + age + "," + health_status + "," + type + "," + shelter_id + ","+ wasRequested;
    }


}
