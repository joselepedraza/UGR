#encoding: utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require "singleton"
require_relative "bad_consequence.rb"
require_relative "prize.rb"
require_relative "treasure_kind.rb"
require_relative "monster.rb"
require_relative "treasure.rb"
require_relative "death_bad_consequence.rb"
require_relative "specific_bad_consequence.rb"
require_relative "numeric_bad_consequence.rb"
require_relative "cultist.rb"
require_relative "cultist_player.rb"
module NapakalakiGame

class CardDealer
  
  include Singleton
  
  @@max_value_treasures=10
  
  attr_accessor :unusedTreasures
  attr_accessor :unusedMonsters
  attr_accessor :usedTreasures
  attr_accessor :usedMonsters
  attr_reader :cardDealer
  attr_accessor :unusedCultists
  
  def initialize
   # @cardDealer= CardDealer.instance
    @unusedTreasures=Array.new
    @unusedMonsters=Array.new
    @usedMonsters=Array.new
    @usedTreasures=Array.new
    @unusedCultists = Array.new
  end
  
  def initTreasureCardDeck
    @unusedTreasures << Treasure.new("Sí mi amo!",4,TreasureKind::HELMET)
    @unusedTreasures << Treasure.new("Botas de investigación",3,TreasureKind::SHOES)
    @unusedTreasures << Treasure.new("Capucha de Cthulhu",3,TreasureKind::HELMET)
    @unusedTreasures << Treasure.new("A prueba de babas",2,TreasureKind::ARMOR)
    @unusedTreasures << Treasure.new("Botas de lluvia ácida",1,TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Casco minero",2,TreasureKind::HELMET)
    @unusedTreasures << Treasure.new("Ametralladora ACME",4,TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Camiseta de la ETSIIT",1,TreasureKind::ARMOR)
    @unusedTreasures << Treasure.new("Clavo de rail ferroviario",3,TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Cuchillo de sushi arcano",2,TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Fez alópodo",3,TreasureKind::HELMET)
    @unusedTreasures << Treasure.new("Hacha prehistórica",2,TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("El aparato del Pr. Tesla",4,TreasureKind::ARMOR)
    @unusedTreasures << Treasure.new("Gaita",4,TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Insecticida",2,TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Escopeta de 3 cañones",4,TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Garabato mistico",2,TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("La rebeca metálica",2,TreasureKind::ARMOR)
    @unusedTreasures << Treasure.new("Necro-playboycon",3,TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Lanzallamas",4,TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Necro-comicón",1,TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Necronomicón",5,TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Linterna a 2 manos",3,TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Necro-gnomicón",2,TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Necrotelecom",2,TreasureKind::HELMET)
    @unusedTreasures << Treasure.new("Porra preternatural",2,TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Tentácula de pega",2,TreasureKind::HELMET)
    @unusedTreasures << Treasure.new("Zapato deja-amigos",1,TreasureKind::SHOES)
    @unusedTreasures << Treasure.new("Shogulador",1,TreasureKind::BOTHHANDS)
    @unusedTreasures << Treasure.new("Varita de atizamiento",3,TreasureKind::ONEHAND)
    @unusedTreasures << Treasure.new("Mazo de los antiguos",3,TreasureKind::ONEHAND)
  end
  
  def initMonstersCardDeck
    #Creamos todas las cartas:
    pr1 = Prize.new(3,2)
    badc1 = NumericBadConsequence.new("Pierdes 5 niveles y 3 tesoros visibles", 5, 3, 0)
    @unusedMonsters<< Monster.new("El rey rosado",13,pr1,badc1)

    pr2 = Prize.new(4,1)
    badc2 = SpecificBadConsequence.new("Te atrapan para llevarte de fiesta y te dejan caer en mitad del vuelo. Descarta 1 mano visible y 1 mano oculta", 0, [TreasureKind::ONEHAND], [TreasureKind::ONEHAND])
    @unusedMonsters<< Monster.new("Demonios de Magaluf",2,pr2,badc2)

    pr3 = Prize.new(2,1)
    badc3 = SpecificBadConsequence.new("Pierdes tu armadura visible y otra oculta", 0, [TreasureKind::ARMOR], [TreasureKind::ARMOR])
    @unusedMonsters<< Monster.new("Byakhees de bonanza",8,pr3,badc3)

    pr4 = Prize.new(1,1)
    badc4 = SpecificBadConsequence.new("Embobados con el lindo primigenio te descartas de tu casco visible", 0, [TreasureKind::HELMET], [])
    @unusedMonsters<< Monster.new("Tenochtitlan",2,pr4,badc4)
    
    pr5 = Prize.new(1,1)
    badc5 = SpecificBadConsequence.new("El primordial bostezo contagioso. Pierdes el calzado visible", 0, [TreasureKind::SHOES], [])
    @unusedMonsters<< Monster.new("El sopor de Dunwich",2,pr5,badc5)

    pr6 = Prize.new(3,1)
    badc6 = NumericBadConsequence.new("Pierdes todos tus tesoros visibles",0,@@max_value_treasures,0)
    @unusedMonsters<< Monster.new("El gorron en el umbral",13,pr6,badc6)

    pr7 = Prize.new(2,1)
    badc7 = SpecificBadConsequence.new("Pierdes la armadura visible", 0, [TreasureKind::ARMOR], [])
    @unusedMonsters<< Monster.new("H.P. Munchcraft",6,pr7,badc7)

    pr8 = Prize.new(1,1)
    badc8 = SpecificBadConsequence.new("Sientes bichos bajo la ropa. Descarta la armadura visible", 0, [TreasureKind::ARMOR], [])
    @unusedMonsters<< Monster.new("Necrófago",13,pr8,badc8)

    pr9 = Prize.new(1,1)
    badc9 = NumericBadConsequence.new("Toses los pulmones y pierdes 2 niveles", 2, 0, 0)
    @unusedMonsters<< Monster.new("Flecher",2,pr9,badc9)

    pr10 = Prize.new(2,1)
    badc10 = DeathBadConsequence.new("Estos monstruos resultan bastante superficiales y te aburren mortalmente. Estás muerto")
    @unusedMonsters<< Monster.new("Los hondos",8,pr10,badc10)

    pr11 = Prize.new(2,1)
    badc11 = NumericBadConsequence.new("Pierdes 2 niveles y 2 tesoros ocultos", 2, 0, 2)
    @unusedMonsters<< Monster.new("Semillas Cthulhu",4,pr11,badc11)

    pr12 = Prize.new(2,1)
    badc12 = NumericBadConsequence.new("Te intentas escaquear. Pierdes una mano visible", 0, 1, 0)
    @unusedMonsters<< Monster.new("Dameargo",1,pr12,badc12)

    pr13 = Prize.new(2,1)
    badc13 = NumericBadConsequence.new("Da mucho asquito. Pierdes 3 niveles", 3, 0, 0)
    @unusedMonsters<< Monster.new("Pollipólipo volante", 3, pr13, badc13)

    pr14 = Prize.new(3,1)
    badc14 = DeathBadConsequence.new("No le hace gracia que pronuncien mal su nombre. Estás muerto")
    @unusedMonsters<< Monster.new("Yskhtihyssg-Goth",14,pr14,badc14)

    pr15 = Prize.new(3,1)
    badc15 = DeathBadConsequence.new("La familia te atrapa. Estas muerto")
    @unusedMonsters<< Monster.new("Familia feliz",1,pr15,badc15)

    pr16 = Prize.new(2,1)
    badc16= SpecificBadConsequence.new("La quinta directiva primaria te obliga a perder 2 niveles y un tesoro de 2 manos",2, [TreasureKind::BOTHHANDS],[])
    @unusedMonsters<< Monster.new("Roboggoth",8,pr16,badc16)

    pr17 = Prize.new(1,1)
    badc17 = SpecificBadConsequence.new("Te asusta en la noche. Pierdes un casco visible.",0,[TreasureKind::HELMET],[])
    @unusedMonsters<< Monster.new("El espia sordo",5,pr17,badc17)

    pr18 = Prize.new(2,1)
    badc18= NumericBadConsequence.new("Menudo susto te llevas. Pierdes 2 niveles y 5 tesoros visibles",2,5,0)
    @unusedMonsters << Monster.new("Tongue", 19,pr18,badc18)

    pr19 = Prize.new(2,1)
    badc19= SpecificBadConsequence.new("Te faltan manos para tanta cabeza. Pierdes 3 niveles y tus tesoros visibles de las manos",3,[[TreasureKind::ONEHAND],[TreasureKind::ONEHAND],[TreasureKind::BOTHHANDS]],[])
    @unusedMonsters << Monster.new("Bicefalo",21,pr19,badc19)
    
    #MONSTRUOS CON SECTARIOS
    pr20 = Prize.new(3,1)
    bc20 = SpecificBadConsequence.new("Pierdes 1 mano visible",0,[TreasureKind::ONEHAND],[])
    @unusedMonsters << Monster.newMonster("El mal indecible impronunciable",10,pr20,bc20,-2)
    
    pr21 = Prize.new(2,1)
    bc21 = SpecificBadConsequence.new("Pierdes tus tesoros visibles. Jajaja.", 0, [[TreasureKind::ONEHAND],[TreasureKind::ONEHAND],[TreasureKind::BOTHHANDS],[TreasureKind::HELMET],[TreasureKind::ARMOR],[TreasureKind::SHOES]], [])
    @unusedMonsters << Monster.newMonster("Testigos Coulares",6,pr21,bc21,2)
    
    pr22 = Prize.new(2,5)
    bc22= DeathBadConsequence.new("Hoy no es tu dia de suerte. Mueres,")
    @unusedMonsters << Monster.newMonster("El gran Cuthulu",20,pr22,bc22,4)
    
    pr23 = Prize.new(2,1)
    bc23 = NumericBadConsequence.new("Tu gobierno te recorta 2 niveles", 2, 0, 0)
    @unusedMonsters << Monster.newMonster("Serpiente Politica",8,pr23,bc23,-2)
    
    pr24 = Prize.new(1,1)
    bc24 = SpecificBadConsequence.new("Pierdes tu casco y tu armadura visible. Pierdes tus manos ocultas", 0,
      [[TreasureKind::HELMET],[TreasureKind::ARMOR]],[TreasureKind::BOTHHANDS])
    @unusedMonsters << Monster.newMonster("Felpuggoth", 2,pr24,bc24,5)
    
    pr25 = Prize.new(4,2)
    bc25 = NumericBadConsequence.new("Pierdes 2 nieves", 2, 0, 0)
    @unusedMonsters << Monster.newMonster("Shoggoth",16,pr25,bc25,-4)
    
    pr26 = Prize.new(1,1)
    bc26 = NumericBadConsequence.new("Pintalabios negro. Pierdes 2 nieves", 2, 0, 0)
    @unusedMonsters << Monster.newMonster("Lolitagooth", 2, pr26, bc26,3)
  end
  
  def initCultistCardDeck
    @unusedCultists << Cultist.new("Secretario",1)
    @unusedCultists << Cultist.new("Secretario",2)
    @unusedCultists << Cultist.new("Secretario",1)
    @unusedCultists << Cultist.new("Secretario",2)
    @unusedCultists << Cultist.new("Secretario",1)
    @unusedCultists << Cultist.new("Secretario",1)
  end
  
  def initCards
    initMonstersCardDeck
    shuffleMonsters
    
    initTreasureCardDeck
    shuffleTreasures
    
    initCultistCardDeck
    shuffleCultists
  end
  
  def shuffleTreasures
    @unusedTreasures.shuffle!
  end
  
  def shuffleMonsters
    @unusedMonsters.shuffle!
  end
  
  def shuffleCultists
    @unusedCultists.shuffle!
  end
  
  def nextCultist
    if @unusedCultists.empty?
      initCultistCardDeck
      shuffleCultist
    end
    c = @unusedCultists.at(0)
    c
  end
  
  def giveTreasureBack(t)
    @usedTreasures<<t
  end
  
  def giveMonsterBack(m)
    @usedMonsters<<m
  end
  
  def nextMonster
    if @unusedMonsters.empty?   #comprobamos si tiene cartas en el mazo
      @usedMonsters.each do |m| #agregamos las cartas descartadas al mazo sin usar
        @unusedMonsters<<m
      end
      
      shuffleMonsters  #barajamos
      @usedMonsters.clear #limpiamos mazo de descartes
    end 
    m=@unusedMonsters.at(0) #cogemos la primera carta del mazo
    giveMonsterBack(m)         #la agregamos al mazo de descartes
    @unusedMonsters.delete(m) #la eliminamos del mazo
    #m                       #y devolvemos la carta
    #@unusedMonsters.at(0)    
    m
  end

  def nextTreasure
    if @unusedTreasures.empty?
      @usedTreasures.each do |t|
        @unusedTreasures<<t
      end
      
      shuffleTreasures
      @usedTreasures.clear
    end
    t=@unusedTreasures.at(0)
    @usedTreasures<<t
    @unusedTreasures.delete(t)
    t
  end
  
  def self.getInstance
   CardDealer.instance
  end
  
  
end

end