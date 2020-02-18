/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalaki;
import java.util.*;
import GUI.Dice;
/**
 *
 * @author joseperoman
 */
public class Player {
    protected static final int MAXLEVEL = 10;       //final en vez de const 
    private String name;
    private int level;
    private boolean dead = true; 
    private boolean canISteal = true;  
    private BadConsequence pendingbadc; 
    private Player enemigo;
    private ArrayList <Treasure> visibleTreasures = new ArrayList();
    private ArrayList <Treasure> hiddenTreasures = new ArrayList();

    /*public Player() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    */
    public Player getEnemy(){
        return this.enemigo;
    }
    
    public Player(String nm){
        name = nm;
        level= 1;
        pendingbadc = new DeathBadConsequence("", false);
    }
    public Player (Player p){
        name=p.name;
        level=p.level;
        pendingbadc = p.pendingbadc;
        visibleTreasures=p.getVisibleTreasures();
        hiddenTreasures=p.getHiddenTreasures();
        enemigo= p.getEnemy();
    }
    public String getName(){
        return name; 
    }
    
    private void bringToLife(){
        dead = true;        //si vuelve a la vida, porque true?
    }
    
    public int getCombatLevel(){
        int cblvl= level;
        for(Treasure t : visibleTreasures){
            cblvl+= t.getBonus();
        }
        if(cblvl<1){
            cblvl=1;
        }
        return cblvl;
    }
    
    private void incrementLevels(int maslvl){
        level = level + maslvl;
    }
    
    private void decrementLevels(int menoslvl){
        level = level - menoslvl;
        if(level<1){
            level=1;
        }
    }
    
    private void setPendingBadConsequence(BadConsequence bc){
        pendingbadc = bc;
    }
    
    private void applyPrize(Monster m){   
        int nLevels= m.getLevelsGained();
        this.incrementLevels(nLevels);
        int nTreasures= m.getTreasuresGained();
        if(nTreasures>0){
            CardDealer dealer = CardDealer.getInstance();
            for(int i=0 ; i<nTreasures;i++){
                Treasure t = dealer.nextTreasure();
                this.hiddenTreasures.add(t);
        }
        }
    }

    private void applyBadConsequence(Monster m){
        BadConsequence badConsequence = m.getBadConsequence();
        int nLevels = badConsequence.getLevels();
        decrementLevels(nLevels);
        BadConsequence pendingBad = badConsequence.adjustToFitTreasureList(visibleTreasures, hiddenTreasures);
        this.setPendingBadConsequence(pendingBad);
    }
    
    private boolean canMakeTreasureVisible(Treasure t){
        boolean resultado=false;
        if(visibleTreasures.size()<4){
            TreasureKind tesoro = t.getType();
            switch (tesoro){
                case ONEHAND:
                    if(TesoroEnUso(TreasureKind.BOTHHANDS)){
                        resultado=false;
                    }
                    else{
                        int cont =this.howManyVisibleTreasures(TreasureKind.ONEHAND);                                                   
                        if(cont==2){
                            resultado=false;
                        }
                        else resultado=true;
                    }
                    break;
                default:
                  resultado=!TesoroEnUso(t.getType());
                  break;                              
            }
        }
        return resultado;
    }
    
    private int howManyVisibleTreasures(TreasureKind tKind){
        //Devuelve el número de tesoros visibles de tipo tKind que tiene el jugador.
        int howmany = 0;
        for (Treasure t : visibleTreasures) {   //creo que hay que añadir dos arraylist en esta clase (visibleTreasures y hiddenTreasures)
            if (t.getType() == tKind) {
                howmany++;
            }
        }
        return howmany;
    }
    
    private void dieIfNoTreasures(){
        if( visibleTreasures.isEmpty() && hiddenTreasures.isEmpty()){
            dead=true;
        }
    }
    
    public boolean isDead(){
        return dead;
    }
    
    public ArrayList<Treasure> getHiddenTreasures(){
        return hiddenTreasures;
    }
    
    public ArrayList<Treasure> getVisibleTreasures(){
        return visibleTreasures;
    }
    
    public CombatResult combat(Monster m){ 
        CombatResult result;
        int myLevel=this.getCombatLevel();
        int monsterLevel= this.getOponentLevel(m);
        if(!this.canISteal()){
            Dice dice= Dice.getInstance();
            int nm = dice.nextNumber();
            if(nm < 3 ){
                this.enemigo.getCombatLevel();   
            }
        }
        if(myLevel>monsterLevel){
               this.applyPrize(m);
                if (this.level >= MAXLEVEL) {
                result = CombatResult.WINGAME;
            } else {
                result = CombatResult.WIN;
            }         
        }
        else{
            if(this.shouldConvert()){
                System.out.print("Se convierte en sectario");
                result = CombatResult.LOSEANDCONVERT;      
            }
            else{
            this.applyBadConsequence(m);
            result= CombatResult.LOSE;
            }
        }
        return result;
    } 
    public void makeTreasureVisible(Treasure t){   
        boolean can = this.canMakeTreasureVisible(t);
        if(can){
            this.visibleTreasures.add(t);
            this.hiddenTreasures.remove(t);
        }
    }
    
    public void discardVisibleTreasure(Treasure t){   
 
        this.visibleTreasures.remove(t); //1.2.1

        if (this.pendingbadc!= null && !this.pendingbadc.isEmpty()) {

            this.pendingbadc.substractVisibleTreasure(t);

        }

        this.dieIfNoTreasures();
    }  
    
    public void discardHiddenTreasure(Treasure t){    
        
        this.hiddenTreasures.remove(t); //1.2.1

        if (this.pendingbadc!= null && !this.pendingbadc.isEmpty()) {

            this.pendingbadc.substractHiddenTreasure(t);

        }

        this.dieIfNoTreasures();
    }  
    
    
    public boolean validState(){
        boolean valid=false;
        if(pendingbadc.isEmpty() && (hiddenTreasures.size()<=4)){      
            valid=true;
        }
        return valid;
    }
    
    public void initTreasures(){
        CardDealer dealer = CardDealer.getInstance();
        Dice dice = Dice.getInstance();
        this.bringToLife();
        
        Treasure treasure = dealer.nextTreasure();
        this.hiddenTreasures.add(treasure);
        
        int number = dice.nextNumber();
        if(number>1){
            Treasure treas= dealer.nextTreasure();
            this.hiddenTreasures.add(treas);
        }
        if(number==6){
            Treasure treas= dealer.nextTreasure();
            this.hiddenTreasures.add(treas);
        }
        
    }
    
    public int getLevels(){
        return level;
    }
    
    public Treasure stealTreasure(){
        boolean canI = this.canISteal();
        Treasure t = null;
        if(canI){
            boolean canYou=enemigo.canYouGiveMeATreasure();
            if(canYou){
                t= enemigo.giveMeATreasure();
                this.hiddenTreasures.add(t);
                this.haveStolen(); 
            }
            
        }
        return t;
    }
    
    public void setEnemy(Player enemy){
        //Asigna valor al atributo que referencia al enemigo del jugador.
        enemigo = enemy;
    }
    
     protected Treasure giveMeATreasure(){
           Random rand= new Random();
           int aleatorio=rand.nextInt(hiddenTreasures.size());
           Treasure treasureARobar = hiddenTreasures.get(aleatorio); 
           hiddenTreasures.remove(treasureARobar);

           return treasureARobar;
        
    }
    
    public boolean canISteal(){
        //Devuelve el valor de la variable canISteal, que indica si el jugador ha robado antes o no un tesoro a su enemigo.
        return canISteal;
    }
    
    protected boolean canYouGiveMeATreasure(){
        //Devuelve true si el jugador tiene tesoros para ser robados por otro jugador y false en caso contrario.
        boolean can=false;
        if(hiddenTreasures.size()>0){
            can=true;
        }
        return can;   
    }
    
    private void haveStolen(){
       //Cambia el atributo canISteal a false cuando el jugador roba un tesoro.
       if(canISteal() == true){
           canISteal = false;
       }
    }
    
    public void discardAllTreasures(){
        ArrayList <Treasure> vT = new ArrayList(visibleTreasures);
        for(Treasure t : vT){
            this.discardVisibleTreasure(t);
        }
        ArrayList <Treasure> hT = new ArrayList(hiddenTreasures);
        for(Treasure t : hT){
            this.discardHiddenTreasure(t);
        }
    }

    //METODO INVENTADO POR MI PARA SABER SI UN TESORO ESTA EN VISIBLES PARA USAR EL METODO CANMAKETREASUREVISIBLE
      private boolean TesoroEnUso(TreasureKind type) {
        boolean result = false;
        for (Treasure tipo : this.visibleTreasures) {
            if (type==tipo.getType()) {
                result = true;
                break;
            }
        }
        return result;
    }
      public BadConsequence getPendingBad(){
          return pendingbadc;
      }
      public String toString(){
          return "Nombre: " +name + "       Nivel: "+ Integer.toString(level)+" Nivel De Combate: "+  Integer.toString(this.getCombatLevel()) +" Pending: "+this.pendingbadc;//+ "\nEnemigo: "+ enemigo.name + "     Nivel " + Integer.toString(enemigo.level)+" Nivel De Combate: "+ Integer.toString(enemigo.getCombatLevel());
      }
      
      protected int getOponentLevel(Monster m){
          return m.getCombatLevel();
      }
      protected boolean shouldConvert(){
         Dice dice= Dice.getInstance();
          int num = dice.nextNumber();
          System.out.print("El dado es un "+Integer.toString(num)+"\n");          
           if(num==1){
               return true;
           }
           return false;
      }
      
}
      
