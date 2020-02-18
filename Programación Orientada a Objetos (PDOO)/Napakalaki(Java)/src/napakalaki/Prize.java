/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalaki;

/**
 *
 * @author joseperoman
 */
public class Prize {
    private int treasures;
    private int level;
    
    public Prize(int trss, int lvl){
        treasures = trss;
        level = lvl;
    }
    
    public int getTreasures(){
        return treasures;
    }
    
    public int getLevel(){
        return level;
    }
    
    public String toString(){
        return " \n\tTreasures = " + Integer.toString(treasures) + "; \n\tLevel = " + Integer.toString(level);
    }
}
