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
public class DeathBadConsequence extends NumericBadConsequence{
    private boolean death;
    public DeathBadConsequence(String txt,boolean dead){
        super(txt,0,0,0);
        this.death=dead;
    }
    
    public boolean getDeath(){
        return death;
    }
    
    @Override
    public boolean isEmpty(){
        boolean isEmpty = false;   
        if(this.death==false){
                isEmpty = true;
        }
        return isEmpty;
    }
    
    public String toString(){
        return /*" \n\tTexto = " + text + */" \n\tLevels = " + Integer.toString(levels) +" \n\tDeath = " + Boolean.toString(death);
    }
}
