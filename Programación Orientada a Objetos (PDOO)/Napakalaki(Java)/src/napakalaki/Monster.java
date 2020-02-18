/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalaki;

public class Monster {
    private String name;
    private int combatLevel;
    private Prize prize;
    private BadConsequence badc;
    private int levelChangeAgainstCultistPlayer=0;
    
    public Monster(String nam, int clvl, BadConsequence bc, Prize prz){
        name = nam;
        combatLevel = clvl;
        prize = prz;
        badc = bc;   
    }
    public Monster(String nam, int clvl, BadConsequence bc, Prize prz, int IC){
        name=nam;
        combatLevel=clvl;
        badc=bc;
        prize=prz;
        levelChangeAgainstCultistPlayer=IC;
    }
    
    public String getName(){
        return name;
    }
    public int getCombatLevel(){
        return combatLevel;
    }
    public Prize getPrize(){
        return prize;
    }
    public BadConsequence getBadConsequence(){
        return badc;
    }
    public int getLevelsGained(){
        //Devuelve el número de niveles ganados proporcionados por su buen rollo.
        return prize.getLevel();
    }
    public int getTreasuresGained(){
        //Devuelve el número de tesoros ganados proporcionados por su buen rollo.    
        return prize.getTreasures();
    }
    
    public int getCombatLevelAgainstCultistPlayer(){
        return (getCombatLevel()+levelChangeAgainstCultistPlayer);
    }
    
    
    public String toString(){
        return " \n\nName = " + name + " \nCombat Level = " + Integer.toString(combatLevel) + " \nPrize: " + prize.toString() + " \nBad Consequence: " + badc.toString();
    }
}
