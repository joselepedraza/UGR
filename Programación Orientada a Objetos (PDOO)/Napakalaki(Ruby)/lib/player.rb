# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.


require_relative "dice.rb"
require_relative "combat_result.rb"
require_relative "bad_consequence.rb"

module NapakalakiGame
class Player
  
  @@MAXLEVEL=10
  attr_accessor :name
  attr_accessor :level
  attr_accessor :dead
  attr_accessor :canISteal
  attr_accessor :pendingbadc    #no se incluye en el initialize
  attr_accessor :visibleTreasures
  attr_accessor :hiddenTreasures
  attr_accessor :enemy
  
  def initialize(nm)
    @name=nm
    @level=1    #El primer nivel de jugador es 1
    @dead=true  #Se inicializan a true según el guión
    @canISteal=true
    @visibleTreasures=Array.new
    @hiddenTreasures=Array.new
    @pendingbadc= BadConsequence.new("",0)
  end
  
  def copiarJugador(p)
    @name=p.name
    @level=p.level
    @dead=p.dead  
    @canISteal=p.canISteal
    @visibleTreasures=p.visibleTreasures
    @hiddenTreasures=p.hiddenTreasures
    @pendingbadc= p.pendingbadc
  end
  
  def self.newNamePlayer(nm)  #creo que no sería necesario
    new(nm)
  end
  
  def self.newPlayerPlayer(p)
    @name=p.name
    @level=p.level
    @pendingbadc=p.pendingbadc
  end
  
  def getOponentLevel(m)
    m.combatLevel
  end

  def shouldConvert
    dice = Dice.instance
    num = dice.nextNumber
    #puts "El dado es un: #{num}"
    cond = false
    if num == 1 then
      #puts "Se combierte en sectario"
      cond = true
    end
    cond
  end
  
  def isDead
    @dead == true
  end
  
  def bringToLife
    @dead=false
  end
  
  def getCombatLevel
    cblvl=@level
    @visibleTreasures.each do|t|
      cblvl=cblvl + t.bonus
    end
    cblvl #más los bonus que le proporcionan los tesoros que tenga equipados
  end
  
  def incrementLevels(maslvl)
    @level = @level + maslvl
  end
  
  def decrementLevels(menoslvl)
    @level = @level-menoslvl
    if @level<1 then
      @level = 1
    end
  end
  
  def setPendingBadConsequence(bc)
    @pendingbadc = bc;
  end
  
  def applyPrize(mnstr)
    nlevels = mnstr.getLevelsGained
    incrementLevels(nlevels)
    ntreasures= mnstr.getTreasuresGained
    
    if(ntreasures>0) then
      dealer = CardDealer.instance
      for i in 0..ntreasures
        treasure= dealer.nextTreasure
        @hiddenTreasures << treasure
      end
    end
  end
  
  def applyBadConsequence(mnstr)
    badConsequence = mnstr.badConsequence
    nlevels = badConsequence.levels
    decrementLevels(nlevels)
    pending_bc = badConsequence.adjustToFitTreasureList(@visibleTreasures, @hiddenTreasures)
    setPendingBadConsequence(pending_bc)
  end
  
  def canMakeTreasureVisible(t)
    result=false
    case t.type
    when TreasureKind::ONEHAND
      if TesoroEnUso(TreasureKind::BOTHHANDS)then #Si está equipado con dos manos no puede agregar un tesoro de una mano
        result = false
      else
        cont=0
        @visibleTreasures.each do |tesoro|  #Recorremos los tesoros visibles para ver si ya tiene alguno de una mano (0, 1 o 2)
          if tesoro.type == TreasureKind::ONEHAND then
            cont = cont + 1;
          end
        end
        
        if cont == 2 then  #Si están las dos manos ocupadas no puede
          result=false
        else            #En caso contrario si que puede
          result=true
        end
      end
    else  #El resto de casos, si esta en uso false, si no true
      result = !TesoroEnUso(t.type)
    end
    
    result
  end
  
  #METODO INVENTADO POR MI PARA SABER SI UN TESORO ESTA EN VISIBLES PARA USAR EL METODO CANMAKETREASUREVISIBLE
  def TesoroEnUso(type)
  result = false
      @visibleTreasures.each do |tesoro|
        if type == tesoro.type then
          result = true
          break
        end
      end
    result  
  end
  
  def howManyVisibleTreasures(tKind)
    #Devuelve el número de tesoros visibles de tipo tKind que tiene el jugador.
      howmany=0
      @visibleTreasures.each do |t|    #creo que tb habria que incluir los dos arrayList como en java
        if t.getType == tKind then
          howmany=howmany+1
        end
      end  
    howmany;
  end
  
  def dieIfNoTreasures()
    if (@visibleTreasures.empty? && @hiddenTreasures.empty?)
        @dead = true
      end
  end
  
  def combat(mnstr)
    mylevel= getCombatLevel #no estoy seguro, quizas es solo @level
    monsterlevel= getOponentLevel(mnstr) #el this??
    
    if !@canISteal then
      dice = Dice.instance
      nm = dice.nextNumber
      if nm < 3 then     
        monsterlevel += @enemy.getCombatLevel
      end
    end
    
    if mylevel > monsterlevel then
      applyPrize(mnstr)
      if @level >= @@MAXLEVEL
        result = CombatResult::WINGAME
      else
        result = CombatResult::WIN
      end
    else
      if shouldConvert then
        result = CombatResult::LOSEANDCONVERT
      else
        applyBadConsequence(mnstr)
        result= CombatResult::LOSE
      end 
    end
    
  result
  end
  
  def makeTreasureVisible(t)
    can = canMakeTreasureVisible(t)
    if can then
      @visibleTreasures<<(t)
      @hiddenTreasures.delete(t)
    end
  end

  def discardVisibleTreasure(t)
    @visibleTreasures.delete(t) #hacer copia e iterar sobre ella
    if @pendingbadc != nil && !@pendingbadc.isEmpty then
      @pendingbadc.substractVisibleTreasures(t)
    end
    dieIfNoTreasures
  end
  
  def discardHiddenTreasure(t)
    @hiddenTreasures.delete(t)  #hacer copia e iterar sobre ella 
    if @pendingbadc != nil && !@pendingbadc.isEmpty then
      @pendingbadc.substractHiddenTreasures(t)
    end
    dieIfNoTreasures
  end
  
  def validState
    (@pendingbadc == nil || @pendingbadc.isEmpty) && @hiddenTreasures.size<=4
  end
  
  def setEnemy(enemy)
    @enemy= enemy
  end
  
  def initTreasures()
    dealer = CardDealer.getInstance
    dice= Dice.instance
    bringToLife
    
    treasure = dealer.nextTreasure
    @hiddenTreasures<<(treasure)
    
    number = dice.nextNumber
    if number > 1 then
      treas = dealer.nextTreasure
      @hiddenTreasures<<(treas)
    end
    if number > 6 then
      treas = dealer.nextNumber
      @hiddenTreasures<<(treas)
    end
  end
  
  def stealTreasure()
    canI = canISteal
    if canI then 
      treasure= @enemy.giveMeATreasure
      @hiddenTreasures << treasure
      t=treasure
    end
    t
  end
  
  def giveMeATreasure()
    random=rand(@hiddenTreasures.length)
    @hiddenTreasures[random]
  end
  
  def canYouGiveMeATreasure()
    can=false
    if @visibleTreasures.size>0 then
      can=true
    end
  can
  end
  
  def haveStolen()
    if canISteal()==true
      @canISteal=false
    end
  end
  
  def discardAllTreasures
    vist = Array.new
    hidt = Array.new
    @visibleTreasures.each do |t|
      vist << t
    end
    @hiddenTreasures.each do |t|
      hidt << t
    end
    
    vist.each do |t|
      discardVisibleTreasure(t)
    end
    hidt.each do |t|
      discardHiddenTreasure(t)
    end
  end
  
  def getVisibleTreasures
      @visibleTreasures
  end
  
  def getHiddenTreasures
      @hiddenTreasures
  end
  
  def to_s
    "Nombre: #{@name}  Nivel: #{@level} Nivel de Combate: #{getCombatLevel} \n Nombre Enemigo: #{@enemy.name}  Nivel Enemigo: #{@enemy.level}  Nivel de Combate del Enemigo: #{@enemy.getCombatLevel}"     
  end
  
 #según internet, aunque me suena que no hace falta, pero por si aca
  def getEnemy
    @enemy
  end
 
end
end