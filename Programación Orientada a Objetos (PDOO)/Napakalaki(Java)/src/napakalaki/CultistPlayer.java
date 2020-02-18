/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package napakalaki;
import java.util.*;
import java.util.Collections;

/**
 *
 * @author Josele
 */
public class CultistPlayer extends Player{
    private static int totalCultistPlayers=0;
    private Cultist myCultistCard;
    
    public CultistPlayer(Player p, Cultist c){
        super(p);
        //enemigo=p.getEnemy();      
        myCultistCard=c;
        totalCultistPlayers++;
    }
     
    @Override
    public int getCombatLevel(){
        float nivel=super.getCombatLevel();
        float lvl= (nivel+ (1/5* nivel))+ myCultistCard.getGainedLevels()*totalCultistPlayers;
        lvl=lvl*100;
        lvl=java.lang.Math.round(lvl);
        lvl=lvl/100;
        
        return (int)lvl;
    }
    @Override
    protected int getOponentLevel(Monster m){
        return m.getCombatLevelAgainstCultistPlayer();
    }
    @Override
    protected boolean shouldConvert(){
        return false;
    }
    @Override
    protected Treasure giveMeATreasure(){
          
        Random rnd = new Random();
        return this.getVisibleTreasures().get(rnd.nextInt(this.getVisibleTreasures().size()));
        
    }
    
    @Override
    protected boolean canYouGiveMeATreasure(){
        int tama= this.getVisibleTreasures().size();
        if(tama>0){
            return true;
        }
        else{
            return false;
        }
    }
  
    public int getTotalCultistPlayers(){
        return totalCultistPlayers;
    }
}
