package com.example.petproj;



public class Adoption {

    private int id=0;
    private Adopter adopter;
    private Pets pet;
    private Shelter shelter;
    private String AdoptionDate; // dd/mm/yyyy
    private String status; // pending || accepted || rejected
    private static int adoptionCounter = 0;



    Adoption( String pet_id, String pet_name , String pet_breed, String pet_age,String adopter_name, String adopter_id , String AdoptionDate , String status,String type,int shelter_id ){
        pet =new Pets();
        adopter=new Adopter();
        adoptionCounter++;
        this.id=adoptionCounter;
        this.pet.id= Integer.parseInt(pet_id);
        this.pet.name=pet_name;
        this.pet.breed=pet_breed;
        this.pet.age=pet_age;
        this.pet.type=type;
        this.pet.shelter_id=shelter_id;
        this.adopter.setID(Integer.parseInt(adopter_id));


        this.adopter.setName(adopter_name);

        this.AdoptionDate=AdoptionDate;
        this.status= status;

    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Adopter getAdopter() {
        return adopter;
    }

    public void setAdopter(Adopter adopter) {
        this.adopter = adopter;
    }

    public Pets getPet() {
        return pet;
    }
    public String get_Pet_type() {
        return pet.type;
    }

    public void setPet(Pets pet) {
        this.pet = pet;
    }

    public String getAdoptionDate() {
        return AdoptionDate;
    }

    public void setAdoptionDate(String adoptionDate) {
        AdoptionDate = adoptionDate;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public Shelter getShelter() {
        return shelter;
    }

    public void setShelter(Shelter shelter) {
        this.shelter = shelter;
    }

    @Override
    public String toString() {

        return id + "," + pet.id + "," + pet.name + "," + pet.breed + "," + pet.age + "," + adopter.getName() + "," + adopter.getID() + "," + AdoptionDate + "," + status + "," + pet.type + "," + pet.shelter_id ;
    }


}




