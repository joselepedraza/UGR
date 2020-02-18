/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalaki;
import java.util.ArrayList;         // ArrayList se encuentra en el paquete java.util
/**
 *
 * @author joseperoman
 */
public abstract class BadConsequence {
    //declarar constante MAXTREASURES (protected)
    protected static final int MAXTREASURES=10;
    protected String text;
    protected int levels;
  

    
    public BadConsequence(String txt, int lvl){
        text = txt;
        levels = lvl;    
    }
  
    
    public String getText(){
        return text;
    }
    public int getLevels(){
        return levels;
    }
   
    
    public abstract boolean isEmpty();
    
    public abstract void substractVisibleTreasure(Treasure t);
    public abstract void substractHiddenTreasure(Treasure t);
   
    
     public abstract BadConsequence adjustToFitTreasureList(ArrayList<Treasure> v, ArrayList<Treasure> h);
    
    
    public String toString(){
        return " \n\tTexto = " + text + " \n\tLevels = " + Integer.toString(levels);
    }
}