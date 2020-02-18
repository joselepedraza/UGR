/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalaki;
import java.util.*;
import java.util.Random;

/**
 *
 * @author joseperoman
 */
public class Napakalaki {
    private static final Napakalaki instance = new Napakalaki();
    private Player currentPlayer;
    private ArrayList <Player> players= new ArrayList();
    private CardDealer dealer=CardDealer.getInstance();
    private Monster currentMonster;

    private void initPlayers(ArrayList <String> names){//names : string []
        for(String s : names){
           players.add(new Player(s));
    }
    }
    private Player nextPlayer(){
        int totalplayers=players.size();
        int nextIndice;
        Player nextplayer;
        
        if(this.currentPlayer==null){
            Random rndm= new Random();
            nextIndice= rndm.nextInt(totalplayers);
        }
        else{
            int currentIndice=this.players.indexOf(this.currentPlayer);
            if(currentIndice==totalplayers-1){
                nextIndice=0;
            }
            else{
                nextIndice= currentIndice+1;
            }
        }
        
        nextplayer = this.players.get(nextIndice);

 
        this.currentPlayer = nextplayer;

        return this.currentPlayer;
    }
  
    private boolean nextTurnAllowed(){
        if(this.currentPlayer==null){
            return true;
        }
        else{
            if(this.currentPlayer.validState()){
                return true;
            }
            else{
                return false;
            }
        }
    }
    private void setEnemies(){
          Random rand=new Random();
          int ret=0;
        for(int i=0; i<players.size();i++){     
        do{
            ret = rand.nextInt(players.size());         
        }while(ret==i);     
        players.get(i).setEnemy(players.get(ret));
        }
           
    }
    
    public static Napakalaki getInstance(){
        return instance;
    }
    
    public CombatResult developCombat(){
       CombatResult combate =  currentPlayer.combat(currentMonster);
       if(combate == CombatResult.LOSEANDCONVERT){
           Cultist c = this.dealer.nextCultist();
           CultistPlayer c1 = new CultistPlayer(currentPlayer,c);
           int IndiceCurrentPlayer = players.indexOf(currentPlayer);  
           for(Player p:players){
               if(p.getEnemy() == currentPlayer){
                   p.setEnemy(c1);
               }                  
           }
           players.set(IndiceCurrentPlayer, c1);
           currentPlayer=c1;
 
       }
       this.dealer.giveMonsterBack(this.currentMonster);      
       return combate;
    }
    public void discardVisibleTreasures(ArrayList <Treasure> treasures){      //treasures : Treasure [1..*]
        for(Treasure t : treasures){
            currentPlayer.discardVisibleTreasure(t);
            this.dealer.giveTreasureBack(t);
        }
    }
    public void discardHiddenTreasures(ArrayList <Treasure> treasures){
        for(Treasure t : treasures){
            currentPlayer.discardHiddenTreasure(t);
            this.dealer.giveTreasureBack(t);
        }
    }
    public void makeTreasuresVisible(ArrayList <Treasure> treasures){
        for(Treasure t : treasures){
            currentPlayer.makeTreasureVisible(t);
        }
        
    }
    
    public void initGame(ArrayList <String> players){     //players : string []
        initPlayers(players);
        setEnemies();
        dealer.initCards();
        nextTurn();
    }
    public Player getCurrentPlayer(){
        return this.currentPlayer;
    }
    public Monster getCurrentMonster(){
        return this.currentMonster;
    }
    public boolean nextTurn(){
        boolean siguienteTurno=nextTurnAllowed();
        if(siguienteTurno){
            currentMonster=dealer.nextMonster();
            currentPlayer=nextPlayer();
            boolean dead = currentPlayer.isDead();
            if(dead){
                currentPlayer.initTreasures();
            }
        }
        return siguienteTurno;
    }
    public boolean endOfGame(CombatResult result){
       if(result == CombatResult.WINGAME){
           return true;
       }
       else return false;
    }    
    
    public static void main(String[] args) {
        
        
    }
}
