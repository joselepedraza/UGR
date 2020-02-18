# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module NapakalakiGame
require_relative "bad_consequence.rb"

class SpecificBadConsequence < BadConsequence
  attr_accessor:specificVisibleTreasures,:specificHiddenTreasures 
  def initialize(txt,lvl,sv,sh)
    super(txt,lvl)
    @specificVisibleTreasures=sv
    @specificHiddenTreasures=sh
  end
  
  def isEmpty
    empty = false
    if @specificHiddenTreasures.size==0 && @specificVisibleTreasures.size==0 then
        empty=true
    end
    empty
  end
  
  def substractVisibleTreasures(t)      
    if (@specificVisibleTreasures.include?(t.type)) 
          @specificVisibleTreasures.delete(t.type)               
    end      
  end
  
  def substractHiddenTreasures(t)
    if (@specificHiddenTreasures.include?(t.type)) 
          @specificHiddenTreasures.delete(t.type)         
    end       
  end
=begin
   def adjustToFitTreasureLists(v, h)
    lH = Array.new
    lV = Array.new
    values = [TreasureKind::ARMOR, TreasureKind::ONEHAND, TreasureKind::BOTHHANDS, TreasureKind::HELMET, TreasureKind::SHOES]
        
    values.each { |tK|
      m1 = 0
      m2 = 0
                
      for i in 0..@specificVisibleTreasures.size-1
        if(@specificVisibleTreasures.at(i) == tK)
          m1 += 1
        end
      end
      for i in 0..v.size-1
        if(v.at(i).type == tK)
          m2 += 1
        end
      end
      for i in 0..[m1, m2].min-1
        lV.push(tK)
      end
                
      m1 = 0
      m2 = 0
                
      for i in 0..@specificHiddenTreasures.size-1
        if(@specificHiddenTreasures.at(i) == tK)
          m1 += 1
        end
      end
      for i in 0..h.size-1
        if(h.at(i).type() == tK)
          m2 += 1
        end
      end
      for i in 0..[m1, m2].min-1
        lH.push(tK)
      end
    }
        
    bc = SpecificBadConsequence.new(@text, 0, lV, lH)
     
    bc
  end
=end
  def adjustToFitTreasureList(v,h)
     igualesv= Array.new
     igualesh= Array.new
      bd = SpecificBadConsequence.new("", 0, 0, 0)

          if(!@specificVisibleTreasures.empty? || !@specificHiddenTreasures.empty?) then
           for i in 0..v.size()-1
               if(@specificVisibleTreasures.include?(v[i].type))
                   igualesv << v[i].type
                   i+= 1
               end
           end

           for i in 0..h.size()-1
               if(@specificHiddenTreasures.include?(h[i].type))
                   igualesh << (h[i].type)
                   i+=1
               end
           end

           bd = SpecificBadConsequence.new(@text, 0, igualesv, igualesh)
          end

      #bd.to_s
      bd    
  end

   def to_s
    "#{@text}\n Niveles perdidos: #{@levels}\n Visible especifico: #{@specificVisibleTreasures}\n Ocultos especificos: #{@specificHiddenTreasures}" 
  end
end

end