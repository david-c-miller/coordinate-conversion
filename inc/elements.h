/*
  Copyright 2016-2017 David C. Miller

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

//elements.h
//contains  definitions and lists for all elements in the periodic table
#pragma once
#include "header.h"

using namespace std;

#ifndef PERIODIC_TABLE_ELEMENTS
#define PERIODIC_TABLE_ELEMENTS

namespace Elements
{
  const string Symbol[] = {"H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca","Sc","Ti","V","Cr","Mn","Fe","Co","Ni","Cu","Zn","Ga","Ge","As","Se","Br","Kr","Rb","Sr","Y","Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn","Sb","Te","I","Xe","Cs","Ba","La","Ce","Pr","Nd","Pm","Sm","Eu","Gd","Tb","Dy","Ho","Er","Tm","Yb","Lu","Hf","Ta","W","Re","Os","Ir","Pt","Au","Hg","Tl","Pb","Bi","Po","At","Rn","Fr","Ra","Ac","Th","Pa","U","Np","Pu","Am","Cm","Bk","Cf","Es","Fm","Md","No","Lr","Rf","Db","Sg","Bh","Hs","Mt","Ds","Rg","Cn","Uut","Fl","Uup","Lv","Uus","Uuo"};
  
  const string Name[] = {"Hydrogen","Helium","Lithium","Beryllium","Boron","Carbon","Nitrogen","Oxygen","Fluorine","Neon","Sodium","Magnesium","Aluminum","Silicon","Phosphorus","Sulfur","Chlorine","Argon","Potassium","Calcium","Scandium","Titanium","Vanadium","Chromium","Manganese","Iron","Cobalt","Nickel","Copper","Zinc","Gallium","Germanium","Arsenic","Selenium","Bromine","Krypton","Rubidium","Strontium","Yttrium","Zirconium","Niobium","Molybdenum","Technetium","Ruthenium","Rhodium","Palladium","Silver","Cadmium","Indium","Tin","Antimony","Tellurium","Iodine","Xenon","Cesium","Barium","Lanthanum","Cerium","Praseodymium","Neodymium","Promethium","Samarium","Europium","Gadolinium","Terbium","Dysprosium","Holmium","Erbium","Thulium","Ytterbium","Lutetium","Hafnium","Tantalum","Tungsten","Rhenium","Osmium","Iridium","Platinum","Gold","Mercury","Thallium","Lead","Bismuth","Polonium","Astatine","Radon","Francium","Radium","Actinium","Thorium","Protactinium","Uranium","Neptunium","Plutonium","Americium","Curium","Berkelium","Californium","Einsteinium","Fermium","Mendelevium","Nobelium","Lawrencium","Rutherfordium","Dubnium","Seaborgium","Bohrium","Hassium","Meitnerium","Darmstadtium","Roentgenium","Copernicium","Ununtrium","Flerovium","Ununpentium","Livermorium","Ununseptium","Ununoctium"};

  enum AtomicSymbol { H , He , Li , Be , B , C , N , O , F , Ne , Na , Mg , Al , Si , P , S , Cl , Ar , K , Ca , Sc , Ti , V , Cr , Mn , Fe , Co , Ni , Cu , Zn , Ga , Ge , As , Se , Br , Kr , Rb , Sr , Y , Zr , Nb , Mo , Tc , Ru , Rh , Pd , Ag , Cd , In , Sn , Sb , Te , I , Xe , Cs , Ba , La , Ce , Pr , Nd , Pm , Sm , Eu , Gd , Tb , Dy , Ho , Er , Tm , Yb , Lu , Hf , Ta , W , Re , Os , Ir , Pt , Au , Hg , Tl , Pb , Bi , Po , At , Rn , Fr , Ra , Ac , Th , Pa , U , Np , Pu , Am , Cm , Bk , Cf , Es , Fm , Md , No , Lr , Rf , Db , Sg , Bh , Hs , Mt , Ds , Rg , Cn , Uut , Fl , Uup , Lv , Uus , Uuo };
  
 enum  AtomicName { Hydrogen , Helium , Lithium , Beryllium , Boron , Carbon , Nitrogen , Oxygen , Fluorine , Neon , Sodium , Magnesium , Aluminum , Silicon , Phosphorus , Sulfur , Chlorine , Argon , Potassium , Calcium , Scandium , Titanium , Vanadium , Chromium , Manganese , Iron , Cobalt , Nickel , Copper , Zinc , Gallium , Germanium , Arsenic , Selenium , Bromine , Krypton , Rubidium , Strontium , Yttrium , Zirconium , Niobium , Molybdenum , Technetium , Ruthenium , Rhodium , Palladium , Silver , Cadmium , Indium , Tin , Antimony , Tellurium , Iodine , Xenon , Cesium , Barium , Lanthanum , Cerium , Praseodymium , Neodymium , Promethium , Samarium , Europium , Gadolinium , Terbium , Dysprosium , Holmium , Erbium , Thulium , Ytterbium , Lutetium , Hafnium , Tantalum , Tungsten , Rhenium , Osmium , Iridium , Platinum , Gold , Mercury , Thallium , Lead , Bismuth , Polonium , Astatine , Radon , Francium , Radium , Actinium , Thorium , Protactinium , Uranium , Neptunium , Plutonium , Americium , Curium , Berkelium , Californium , Einsteinium , Fermium , Mendelevium , Nobelium , Lawrencium , Rutherfordium , Dubnium , Seaborgium , Bohrium , Hassium , Meitnerium , Darmstadtium , Roentgenium , Copernicium , Ununtrium , Flerovium , Ununpentium , Livermorium , Ununseptium , Ununoctium };

#endif
}
