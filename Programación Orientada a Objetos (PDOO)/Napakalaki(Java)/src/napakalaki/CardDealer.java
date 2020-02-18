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
public class CardDealer {
    private static final CardDealer instance=new CardDealer();
    private ArrayList <Treasure> unusedTreasures = new ArrayList();
    private ArrayList <Treasure> usedTreasures = new ArrayList();
    private ArrayList <Monster> unusedMonsters= new ArrayList();
    private ArrayList <Monster> usedMonsters= new ArrayList();
    private ArrayList <Cultist> unusedCultists= new ArrayList();
    
    
    private CardDealer(){
        
    }
    private void initTreasureCardDeck(){
        unusedTreasures.add(new Treasure("¡Śı mi amo!",4,TreasureKind.HELMET));
        unusedTreasures.add(new Treasure("Botas de investigación",3,TreasureKind.SHOES));
        unusedTreasures.add(new Treasure("Capucha de Cthulhu",3,TreasureKind.HELMET));
        unusedTreasures.add(new Treasure("A prueba de babas",2,TreasureKind.ARMOR));
        unusedTreasures.add(new Treasure("Botas de lluvia ácida",1,TreasureKind.BOTHHANDS));
        unusedTreasures.add(new Treasure("Casco minero",2,TreasureKind.HELMET));
        unusedTreasures.add(new Treasure("Ametralladora ACME",4,TreasureKind.BOTHHANDS));
        unusedTreasures.add(new Treasure("Camiseta de la ETSIIT",1, TreasureKind.ARMOR));
        unusedTreasures.add(new Treasure("Clavo de rail ferroviario",3,TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Cuchillo de sushi arcano",2,TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Fez alópodo",3,TreasureKind.HELMET));
        unusedTreasures.add(new Treasure("Hacha prehistórica",2,TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("El aparato del Pr. Tesla",4,TreasureKind.ARMOR));
        unusedTreasures.add(new Treasure("Gaita",4,TreasureKind.BOTHHANDS));
        unusedTreasures.add(new Treasure("Insecticida",2,TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Escopeta de 3 cañones",4,TreasureKind.BOTHHANDS));
        unusedTreasures.add(new Treasure("Garabato mistico",2,TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("La rebeca metálica",2,TreasureKind.ARMOR));
        unusedTreasures.add(new Treasure("Lanzallamas",4,TreasureKind.BOTHHANDS));
        unusedTreasures.add(new Treasure("Necro-comicón",1,TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Necronomicón",5,TreasureKind.BOTHHANDS));
        unusedTreasures.add(new Treasure("Linterna a 2 manos",3, TreasureKind.BOTHHANDS));
        unusedTreasures.add(new Treasure("Necro-gnomicón",2,TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Necrotelecom",2,TreasureKind.HELMET));
        unusedTreasures.add(new Treasure("Mazo de los antiguos",3,TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Necro-playboycon",3,TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Porra preternatural",2,TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Shogulador",1,TreasureKind.BOTHHANDS));
        unusedTreasures.add(new Treasure("Varita de atizamiento",3,TreasureKind.ONEHAND));
        unusedTreasures.add(new Treasure("Tentácula de pega",2,TreasureKind.HELMET));
        unusedTreasures.add(new Treasure("Zapato deja-amigos",1,TreasureKind.SHOES));
    }
    private void initMonsterCardDeck(){
        BadConsequence bc1 = new SpecificBadConsequence("Pierdes tu armadura visible y otra oculta",0,
        new ArrayList(Arrays.asList(TreasureKind.ARMOR)),
        new ArrayList(Arrays.asList(TreasureKind.ARMOR)));
        Prize pr1= new Prize(2,1);
        unusedMonsters.add(new Monster("3 Byakhees de bonanza", 8, bc1, pr1));
        
        BadConsequence bc2= new SpecificBadConsequence("Embobados con el lindo primigenio te descartas de tu casco visible",0,
        new ArrayList(Arrays.asList(TreasureKind.HELMET)),
        new ArrayList());
        Prize pr2= new Prize(1,1);
        unusedMonsters.add(new Monster("Tenochtitlan",2,bc2,pr2));
        
        BadConsequence bc3= new SpecificBadConsequence("El primordial bostezo contagioso. Pierdes el calzado visible",0,
        new ArrayList(Arrays.asList(TreasureKind.SHOES)),
        new ArrayList());
        Prize pr3= new Prize(1,1);
        unusedMonsters.add(new Monster("El sopor de Dunwich",2,bc3,pr3));
        
        BadConsequence bc4 =  new SpecificBadConsequence("Te atrapan para llevarte de fiesta y te dejan caer en mitad del vuelo. Descarta 1 mano visible y 1 oculta",0,
        new ArrayList(Arrays.asList(TreasureKind.ONEHAND)),
        new ArrayList(Arrays.asList(TreasureKind.ONEHAND)));
        Prize pr4= new Prize(4,1);
        unusedMonsters.add(new Monster("Demonios de Magaluf",2,bc4,pr4));
        
        BadConsequence bc5= new SpecificBadConsequence("Pierdes todos tus tesoros visibles",0,
        new ArrayList(Arrays.asList(TreasureKind.HELMET,TreasureKind.ONEHAND,TreasureKind.BOTHHANDS,TreasureKind.ARMOR,TreasureKind.SHOES)),
        new ArrayList());
        Prize pr5= new Prize(3,1);
        unusedMonsters.add(new Monster("El gorron en el umbral",13,bc5,pr5));
        
        BadConsequence bc6= new SpecificBadConsequence("Pierdes la armadura visible",0,
        new ArrayList(Arrays.asList(TreasureKind.ARMOR)),
        new ArrayList());
        Prize pr6= new Prize(2,1);
        unusedMonsters.add(new Monster("H.P. Munchcraft",6,bc6,pr6));
        
        BadConsequence bc7= new SpecificBadConsequence("Sientes bichos bajo la ropa. Descarta la armadura visible",0,
        new ArrayList(Arrays.asList(TreasureKind.ARMOR)),
        new ArrayList());
        Prize pr7 = new Prize(1,1);
        unusedMonsters.add(new Monster("Necrofago",13,bc7,pr7));
        
        BadConsequence bc8 = new NumericBadConsequence("Pierdes 5 niveles y 3 tesoros visibles", 5, 3, 0);
        Prize pr8 = new Prize(3,2);
        unusedMonsters.add(new Monster("El rey de rosa", 11, bc8, pr8));
        
        BadConsequence bc9= new NumericBadConsequence("Toses los pulmones y pierdes 2 niveles",2,0,0);
        Prize pr9= new Prize(1,1);
        unusedMonsters.add(new Monster("Flecher",2,bc9,pr9));
        
        BadConsequence bc10 = new DeathBadConsequence ("Estos monstruos resultan bastante superficiales y te aburren mortalmente. Estas muerto", true);
        Prize pr10 = new Prize(2,1);
        unusedMonsters.add(new Monster("Los hondos", 8, bc10, pr10));
        
        BadConsequence bc11 = new NumericBadConsequence("Pierdes 2 niveles y dos tesoros ocultos.", 2, 0, 2);
        Prize pr11 = new Prize(2, 1);
        unusedMonsters.add(new Monster("Semillas Cthulhu", 4, bc11, pr11));
        
        BadConsequence bc12 = new SpecificBadConsequence("Te intentas escaquear. Pierdes una mano visible.", 0,
        new ArrayList(Arrays.asList(TreasureKind.ONEHAND)),
        new ArrayList());
        Prize pr12 = new Prize(2,1);
        unusedMonsters.add(new Monster("Dameargo",1, bc12, pr12));
        
        BadConsequence bc13 = new NumericBadConsequence("Da mucho asquito. Pierdes 3 niveles", 3, 0, 0);
        Prize pr13 = new Prize(2, 1);
        unusedMonsters.add(new Monster("Pollipólipo volante", 3, bc13, pr13));
        
        BadConsequence bc14 = new DeathBadConsequence("No le hace gracia que pronuncien mal su nombre. Estas muerto", true);
        Prize pr14 = new Prize (3,1);
        unusedMonsters.add(new Monster("Yskhtihyssg-Goth", 14, bc14, pr14));
        
        BadConsequence bc15 = new DeathBadConsequence("La familia te atrapa. Estas muerto", true);
        Prize pr15 = new Prize(3, 1);
        unusedMonsters.add(new Monster("Familia feliz", 1, bc15, pr15));
             
        BadConsequence bc16 = new SpecificBadConsequence("La quinta directiva primaria te obliga a perder 2 niveles y un tesoro 2 manos visible.", 2,
        new ArrayList(Arrays.asList(TreasureKind.BOTHHANDS)),
        new ArrayList());
        Prize pr16 = new Prize(2, 1);
        unusedMonsters.add(new Monster("Roboggoth", 8, bc16, pr16));
        
        BadConsequence bc17 = new SpecificBadConsequence("Te asusta en la noche. Pierdes un casco visible.", 0,
        new ArrayList(Arrays.asList(TreasureKind.HELMET)),
        new ArrayList());
        Prize pr17 = new Prize(2, 1);
        unusedMonsters.add(new Monster("El espia sordo", 5, bc17, pr17)); 
        
        BadConsequence bc18 = new NumericBadConsequence("Menudo susto te llevas. Pierdes 2 niveles y 5 tesoros visibles", 2, 5, 0);
        Prize pr18 = new Prize(2,1);
        unusedMonsters.add(new Monster("Tongue", 19, bc18, pr18));
    
        BadConsequence bc19 = new SpecificBadConsequence("Te faltan manos para tanta cabeza. Pierdes 3 niveles y tus tesoros visibles de las manos", 3,
        new ArrayList(Arrays.asList(TreasureKind.BOTHHANDS, TreasureKind.ONEHAND, TreasureKind.ONEHAND)),
        new ArrayList());
        Prize pr19 = new Prize(2,1);
        unusedMonsters.add(new Monster("Bicéfalo",21, bc19, pr19)); 
         
    //----------------------------------Monstruos con Secretarios-----------------------------------------------------------------------------
        BadConsequence bc20 = new SpecificBadConsequence("Pierdes 1 mano visible",0,new ArrayList(Arrays.asList(TreasureKind.ONEHAND)),new ArrayList());
        Prize pr20 = new Prize(3,1);
        unusedMonsters.add(new Monster("El mal indecible impronunciable",10,bc20,pr20,-2));
        
        BadConsequence bc21 = new SpecificBadConsequence("Pierdes tus tesoros visibles. Jajaja.",0,
        new ArrayList(Arrays.asList(TreasureKind.ONEHAND,TreasureKind.ONEHAND,TreasureKind.ARMOR,TreasureKind.BOTHHANDS,TreasureKind.HELMET,TreasureKind.SHOES)),new ArrayList());
        Prize pr21= new Prize(2,1);
        unusedMonsters.add(new Monster("Testigos Oculares",6,bc21,pr21,2));
        
        BadConsequence bc22 = new DeathBadConsequence("Hoy no es tu d ́ıa de suerte. Mueres.",true);
        Prize pr22 = new Prize(2,5);
        unusedMonsters.add(new Monster("El gran Cuthulu",20,bc22,pr22,4));
        
        BadConsequence bc23 = new NumericBadConsequence("Tu gobierno te recorta 2 niveles.",2,0,0);
        Prize pr23 = new Prize(2,1);
        unusedMonsters.add(new Monster("Serpiente Politica",8,bc23,pr23,-2));
        
        BadConsequence bc24 = new SpecificBadConsequence("Pierdes tu casco y tu armadura visible. Pierdes tus manos ocultas.",0,
        new ArrayList(Arrays.asList(TreasureKind.HELMET,TreasureKind.ARMOR)),new ArrayList(Arrays.asList(TreasureKind.BOTHHANDS)));
        Prize pr24 = new Prize(1,1);
        unusedMonsters.add(new Monster("Felpuggoth",2,bc24,pr24,5));
        
        BadConsequence bc25 = new NumericBadConsequence("Pierdes 2 niveles",2,0,0);
        Prize pr25 = new Prize(4,2);
        unusedMonsters.add(new Monster("Shoggoth",16,bc25,pr25,-4));
        
        BadConsequence bc26 = new NumericBadConsequence("Pintalabios negro. Pierdes 2 niveles.",2,0,0);
        Prize pr26 = new Prize(1,1);
        unusedMonsters.add(new Monster("Lolitagooth",2,bc26,pr26,3));
    }
    
     private void initCultistCardDeck(){
         unusedCultists.add(new Cultist("Secretario",1));
         unusedCultists.add(new Cultist("Secretario",2));
         unusedCultists.add(new Cultist("Secretario",1));
         unusedCultists.add(new Cultist("Secretario",2));
         unusedCultists.add(new Cultist("Secretario",1));
         unusedCultists.add(new Cultist("Secretario",1));
        
    }
    
    
    
    private void shuffleTreasures(){
        Collections.shuffle(unusedTreasures);
    }
    private void shuffleMonsters(){
        Collections.shuffle(unusedMonsters);
    }
    public static CardDealer getInstance(){
        return instance;
    }
    public Treasure nextTreasure(){
        if(unusedTreasures.isEmpty()){
            for(Treasure t : usedTreasures){
                unusedTreasures.add(t);
            }
            shuffleTreasures();
            usedTreasures.clear();
        }
        Treasure T = unusedTreasures.get(0);
        usedTreasures.add(T);
        unusedTreasures.remove(T);
        return T;                 
    }
    public Monster nextMonster(){
            if(unusedMonsters.isEmpty()){
            for(Monster m : usedMonsters){
                unusedMonsters.add(m);
            }
            shuffleMonsters();
            usedMonsters.clear();
        }
        Monster M = unusedMonsters.get(0);
        usedMonsters.add(M);
        unusedMonsters.remove(0);
        return M;                 
    }
    public void giveTreasureBack(Treasure t){
        usedTreasures.add(t);
    }
    public void giveMonsterBack(Monster m){
        usedMonsters.add(m);
    }
    public void initCards(){
        this.initMonsterCardDeck();
        shuffleMonsters();
        this.initTreasureCardDeck();
        shuffleTreasures();
       
        this.initCultistCardDeck();
        shuffleCultist();
    }
    
    private void shuffleCultist(){
        Collections.shuffle(unusedCultists);
    }
   
    public Cultist nextCultist(){
        if(this.unusedCultists.isEmpty()){
            this.initCultistCardDeck();
            this.shuffleCultist();
        }
        Cultist c = this.unusedCultists.get(0);
        
        return c;
    }
}
