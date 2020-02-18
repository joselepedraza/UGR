# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "bad_consequence.rb"
module NapakalakiGame
class NumericBadConsequence < BadConsequence

  attr_accessor :nVisibleTreasures, :nHiddenTreasures
  def initialize(txt,lvls,nV,nH)
    super(txt,lvls)
    #@text=txt
    #@levels=lvls
    @nVisibleTreasures=nV
    @nHiddenTreasures=nH
  end
 
  def isEmpty()
    empty = false
    if @nVisibleTreasures==0 && @nHiddenTreasures==0 then
        empty=true
    end
      return empty
  end
  
  def substractVisibleTreasures(t)
    if (@nVisibleTreasures > 0) then
       @nVisibleTreasures-=1;
    end 
  end
  
  def substractHiddenTreasures(t)
    if(@nHiddenTreasures > 0)
      @nHiddenTreasures-=1; 
    end
  end
  
  def setnVisibleTreasures(nV)
    @nVisibleTreasures = nV
  end
  
  def setnHiddenTreasures(nH)
    @nHiddenTreasures = nH
  end
  
  def adjustToFitTreasureList(v,h)
    
    nvisible=0
    nhidden=0
  
    if @nVisibleTreasures !=0 || @nHiddenTreasures !=0 then
              
      if(v.size <= @nVisibleTreasures) then
        nvisible = v.size();                      
      else
        nvisible = @nVisibleTreasures;
      end

      if (h.size() <= @nHiddenTreasures) then
        nhidden= h.size()
      else
        nhidden = @nHiddenTreasures
      end
        
      bd = NumericBadConsequence.new(@text, 0, nvisible, nhidden)
    end
    
    bd
  end
  
   def to_s
    "#{@text}\n Niveles perdidos: #{@levels}\n Tesoros visibles: #{@nVisibleTreasures}\n Tesoros ocultos: #{@nHiddenTreasures}"
  end
  
end
end