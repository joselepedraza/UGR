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
public class SpecificBadConsequence extends BadConsequence {
    private ArrayList <TreasureKind> specificVisibleTreasures = new ArrayList();
    private ArrayList <TreasureKind> specificHiddenTreasures = new ArrayList();
    
    public SpecificBadConsequence(String txt, int lvl, ArrayList sv, ArrayList sh){
        super(txt,lvl);
        specificVisibleTreasures=sv;
        specificHiddenTreasures=sh;
    }
    
    public ArrayList <TreasureKind> getspecificVisibleTreasures(){
        return specificVisibleTreasures;
    }
    public ArrayList <TreasureKind> getspecificHiddenTreasures(){
        return specificHiddenTreasures;
    }
    
    @Override
    public boolean isEmpty(){
        boolean empty=false;
        if(specificVisibleTreasures.isEmpty() && specificHiddenTreasures.isEmpty()){
            empty=true;
        }
        return empty;
    }
    @Override
    public void substractVisibleTreasure(Treasure t){
        if(!specificVisibleTreasures.isEmpty()){
            specificVisibleTreasures.remove(t.getType());
        }
    }
    @Override
    public void substractHiddenTreasure(Treasure t){
        if(!specificHiddenTreasures.isEmpty()){
            specificHiddenTreasures.remove(t.getType());
        }
    }
    
    @Override
    public SpecificBadConsequence adjustToFitTreasureList(ArrayList<Treasure> v, ArrayList<Treasure> h){
        ArrayList<TreasureKind> igualesv= new ArrayList();
        ArrayList<TreasureKind> igualesh= new ArrayList();
        
        SpecificBadConsequence sbc = new SpecificBadConsequence("",0,igualesv,igualesh);
        
        if(!this.specificVisibleTreasures.isEmpty() || !this.specificHiddenTreasures.isEmpty()){
            for(int i=0; i<v.size(); i++){
                    if(this.specificVisibleTreasures.contains(v.get(i).getType())){
                        igualesv.add(v.get(i).getType());
                        i++;
                    }
                }
             for(int i=0; i<h.size(); i++){
                    if(this.specificHiddenTreasures.contains(h.get(i).getType())){
                        igualesh.add(h.get(i).getType());
                        i++;
                    }
                }
        }
       sbc= new SpecificBadConsequence(super.getText(),this.getLevels(),igualesv,igualesh);
        
        return sbc;
    }
    
    public String toString(){
        return /*" \n\tTexto = " + text + " \n\tLevels = " + Integer.toString(levels) + */"\n\tTesoros especificos visibles = " + specificVisibleTreasures + "\n\tTesoros especificos ocultos = " + specificHiddenTreasures + "\n";
    }
}
