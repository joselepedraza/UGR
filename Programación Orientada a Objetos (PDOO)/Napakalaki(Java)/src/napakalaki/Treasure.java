/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalaki;
import java.util.ArrayList;

public class Treasure {
    private String name;
    private int bonus;
    private TreasureKind type;
    
    public Treasure(String n, int bns, TreasureKind t){
        name=n;
        bonus=bns;
        type=t;
    }
    public String getName(){
        return name;
    }
    public int getBonus(){
        return bonus;
    }
    public TreasureKind getType(){
        return type;
    }
    public String toString(){
        return "Nombre: "+name+" Bonus: "+  Integer.toString(bonus) + "  Tesoro: "+ type;
    }
}
