/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package napakalaki;

import java.util.ArrayList;

/**
 *
 * @author joseperoman
 */
public class NumericBadConsequence extends BadConsequence{
    private int nVisibleTreasures;
    private int nHiddenTreasures;
    
    public NumericBadConsequence(String txt, int lvl,int nv, int nh){
    super(txt,lvl);
    nVisibleTreasures=nv;
    nHiddenTreasures=nh;
}
    
    public int getnVisibleTreasures(){
        return nVisibleTreasures;
    }
    public int getnHiddenTreasures(){
        return nHiddenTreasures;
    }
    
    @Override
    public boolean isEmpty(){
        boolean empty=false;
        if(nVisibleTreasures == 0 && nHiddenTreasures==0){
            empty=true;
        }
        return empty;
    }
    @Override
    public void substractVisibleTreasure(Treasure t){
        if(nVisibleTreasures>0){
            nVisibleTreasures-=1;
        }
    }
    @Override
    public void substractHiddenTreasure(Treasure t){
        if(nHiddenTreasures>0){
            nHiddenTreasures-=1;
        }
    }
    @Override
    public NumericBadConsequence adjustToFitTreasureList(ArrayList<Treasure> v, ArrayList<Treasure> h){
        int nvisible= 0, nhidden=0;
        
        NumericBadConsequence nbc = new NumericBadConsequence("",0,0,0);
        
        if(v.size() <= this.nVisibleTreasures){
            nvisible=v.size();
        }
        else nvisible=this.nVisibleTreasures;
            
        
        if(h.size() <= nHiddenTreasures){
            nhidden=h.size();
        }
        else nhidden=this.nHiddenTreasures;
        
        nbc= new NumericBadConsequence(this.getText(),this.getLevels(),nvisible,nhidden);
        
        return nbc;
    }
    
    
    public String toString(){
        return /*" \n\tTexto = " + text + */" \n\tLevels = " + Integer.toString(levels) + " \n\tnVisibleTreasures =  " + Integer.toString(nVisibleTreasures) + " \n\tnHiddenTreasures = " + Integer.toString(nHiddenTreasures);
    }
}
