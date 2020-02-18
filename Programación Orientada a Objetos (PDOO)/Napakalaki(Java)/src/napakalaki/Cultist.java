/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalaki;

/**
 *
 * @author Josele
 */
public class Cultist {
    private String name;
    private int gainedLevels;
    
    public Cultist (String nm , int glvl){
        name=nm;
        gainedLevels=glvl;
    }
    public int getGainedLevels(){
        return gainedLevels;
    }
}
