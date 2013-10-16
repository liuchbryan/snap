#include "Table.h"

int main(){
  TTableContext Context;
  // create scheme
  TTable::Schema AnimalS;
  AnimalS.Add(TPair<TStr,TTable::TYPE>("Animal", TTable::STR));
  AnimalS.Add(TPair<TStr,TTable::TYPE>("Size", TTable::STR));
  AnimalS.Add(TPair<TStr,TTable::TYPE>("Location", TTable::STR));
  AnimalS.Add(TPair<TStr,TTable::TYPE>("Number", TTable::INT));
  TIntV RelevantCols;
  RelevantCols.Add(0);
  RelevantCols.Add(1);
  RelevantCols.Add(2);
  // create table
  PTable T = TTable::LoadSS("Animals", AnimalS, "../../testfiles/animals.txt", Context, RelevantCols);
  //PTable T = TTable::LoadSS("Animals", AnimalS, "animals.txt");
  T->Unique("Animal");
  TTable Ts = *T;  // did we fix problem with copy-c'tor ?
  //PTable Ts = TTable::LoadSS("Animals_s", AnimalS, "../../testfiles/animals.txt", RelevantCols);
  //Ts->Unique(AnimalUnique);

  // test Select
  // create predicate tree: find all animals that are big and african or medium and Australian
  TPredicate::TAtomicPredicate A1(TPredicate::STR, true, TPredicate::EQ, "Location", "", 0, 0, "Africa");  
  TPredicate::TPredicateNode N1(A1);  // Location == "Africa"
  TPredicate::TAtomicPredicate A2(TPredicate::STR, true, TPredicate::EQ, "Size", "", 0, 0, "big");  
  TPredicate::TPredicateNode N2(A2);  // Size == "big"
  TPredicate::TPredicateNode N3(TPredicate::AND);
  N3.AddLeftChild(&N1);
  N3.AddRightChild(&N2);
  TPredicate::TAtomicPredicate A4(TPredicate::STR, true, TPredicate::EQ, "Location", "", 0, 0, "Australia");  
  TPredicate::TPredicateNode N4(A4);  
  TPredicate::TAtomicPredicate A5(TPredicate::STR, true, TPredicate::EQ, "Size", "", 0, 0, "medium");  
  TPredicate::TPredicateNode N5(A5); 
  TPredicate::TPredicateNode N6(TPredicate::AND);
  N6.AddLeftChild(&N4);
  N6.AddRightChild(&N5);
  TPredicate::TPredicateNode N7(TPredicate::OR);
  N7.AddLeftChild(&N3);
  N7.AddRightChild(&N6);
  TPredicate Pred(&N7);
  TIntV SelectedRows;
  Ts.Select(Pred, SelectedRows);

  TStrV GroupBy;
  GroupBy.Add("Location");
  T->Group("LocationGroup", GroupBy);
  GroupBy.Add("Size");
  T->Group("LocationSizeGroup", GroupBy);
  T->Count("LocationCount", "Location");
  PTable Tj = T->Join("Location", Ts, "Location");
  TStrV UniqueAnimals;
  UniqueAnimals.Add("Animals_1.Animal");
  UniqueAnimals.Add("Animals_2.Animal");
  Tj->Unique(UniqueAnimals, false);
  //print table
   T->SaveSS("../../testfiles/animals_out_T.txt");
   Ts.SaveSS("../../testfiles/animals_out_Ts.txt");
   Tj->SaveSS("../../testfiles/animals_out_Tj.txt");
  return 0;
}
