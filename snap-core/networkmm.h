#ifndef NETWORKMM_H
#define NETWORKMM_H


class TMMNet;


typedef TPt<TMMNet> PMMNet;

//NOTE: Removed inheritance from nodes and edges (for now)
//TODO: Renaming
//TODO: Change Type everywhere to Mode
//TODO: TMultiLink with the entire hash table

//A single mode in a multimodal directed attributed multigraph
class TMultiNet;

/// Pointer to a directed attribute multigraph (TNEANet)
typedef TPt<TMultiNet> PMultiNet;

//#//////////////////////////////////////////////
/// Directed multigraph with node edge attributes. ##TNEANet::Class
class TMultiNet : TNEANet {
public:
  typedef TMultiNet TNetMM;
  typedef TPt<TMultiNet> PNetMM;
public:
  class TNodeMM  {
  private:
    TInt Id;
    TIntV InEIdV, OutEIdV;
  public:
    TNodeMM() : Id(-1), InEIdV(), OutEIdV() { }
    TNodeMM(const int& NId) : Id(NId), InEIdV(), OutEIdV() { }
    TNodeMM(const TNode& Node) : Id(Node.Id), InEIdV(Node.InEIdV), OutEIdV(Node.OutEIdV) { }
    TNodeMM(TSIn& SIn) : Id(SIn), InEIdV(SIn), OutEIdV(SIn) { }
    void Save(TSOut& SOut) const { Id.Save(SOut); InEIdV.Save(SOut); OutEIdV.Save(SOut); }
    int GetId() const { return Id; }
    int GetDeg() const { return GetInDeg() + GetOutDeg(); } //TODO: Reimplement
    int GetInDeg() const { return InEIdV.Len(); }
    int GetOutDeg() const { return OutEIdV.Len(); }
    int GetInEId(const int& EdgeN) const { return InEIdV[EdgeN]; }
    int GetOutEId(const int& EdgeN) const { return OutEIdV[EdgeN]; }
    int GetNbrEId(const int& EdgeN) const { return EdgeN<GetOutDeg()?GetOutEId(EdgeN):GetInEId(EdgeN-GetOutDeg()); }
    bool IsInEId(const int& EId) const { return InEIdV.SearchBin(EId) != -1; }
    bool IsOutEId(const int& EId) const { return OutEIdV.SearchBin(EId) != -1; }
    friend class TMultiNet;
  };
  class TEdgeMM {
  private:
    TInt Id, SrcNId, DstNId, SrcNTypeId, DstNTypeId;
  public:
    TEdgeMM() : Id(-1), SrcNId(-1), DstNId(-1), SrcNTypeId(-1), DstNTypeId(-1) { }
    TEdgeMM(const int& EId, const int& SourceNId, const int& DestNId, const int& SourceNTypeId, const int& DestNTypeId) : 
      Id(EId), SrcNId(SourceNId), DstNId(DestNId), SrcNTypeId(SourceNTypeId), DstNTypeId(DestNTypeId) { }
    TEdgeMM(const TEdgeMM& EdgeMM) : Id(EdgeMM.Id), SrcNId(EdgeMM.SrcNId), DstNId(EdgeMM.DstNId), SrcNTypeId(EdgeMM.SrcNTypeId), DstNTypeId(EdgeMM.DstNTypeId) { }
    TEdgeMM(TSIn& SIn) : Id(SIn), SrcNId(SIn), DstNId(SIn), SrcNTypeId(SIn), DstNTypeId(SIn) { }
    void Save(TSOut& SOut) const { Id.Save(SOut); SrcNId.Save(SOut); DstNId.Save(SOut); SrcNTypeId(-1).Save(SOut); DstNTypeId.Save(SOut); }
    int GetId() const { return Id; }
    int GetSrcNId() const { return SrcNId; }
    int GetDstNId() const { return DstNId; }
    int GetSrcNTypeId() const { return SrcNTypeId; }
    int GetDstNTypeId() const { return DstNTypeId; }
    friend class TMultiNet;
  };

/*private:
  TNode& GetNode(const int& NId) { return NodeH.GetDat(NId); }
  const TNode& GetNode(const int& NId) const { return NodeH.GetDat(NId); }
  TEdge& GetEdge(const int& EId) { return EdgeH.GetDat(EId); }
  const TEdge& GetEdge(const int& EId) const { return EdgeH.GetDat(EId); }

  /// Get Int node attribute val.  If not a proper attr, return default.
  TInt GetIntAttrDefaultN(const TStr& attribute) const { return IntDefaultsN.IsKey(attribute) ? IntDefaultsN.GetDat(attribute) : (TInt) TInt::Mn; }
  /// Get Str node attribute val.  If not a proper attr, return default.
  TStr GetStrAttrDefaultN(const TStr& attribute) const { return StrDefaultsN.IsKey(attribute) ? StrDefaultsN.GetDat(attribute) : (TStr) TStr::GetNullStr(); }
  /// Get Flt node attribute val.  If not a proper attr, return default.
  TFlt GetFltAttrDefaultN(const TStr& attribute) const { return FltDefaultsN.IsKey(attribute) ? FltDefaultsN.GetDat(attribute) : (TFlt) TFlt::Mn; }
  /// Get Int edge attribute val.  If not a proper attr, return default.
  TInt GetIntAttrDefaultE(const TStr& attribute) const { return IntDefaultsE.IsKey(attribute) ? IntDefaultsE.GetDat(attribute) : (TInt) TInt::Mn; }
  /// Get Str edge attribute val.  If not a proper attr, return default.
  TStr GetStrAttrDefaultE(const TStr& attribute) const { return StrDefaultsE.IsKey(attribute) ? StrDefaultsE.GetDat(attribute) : (TStr) TStr::GetNullStr(); }
  /// Get Flt edge attribute val.  If not a proper attr, return default.
  TFlt GetFltAttrDefaultE(const TStr& attribute) const { return FltDefaultsE.IsKey(attribute) ? FltDefaultsE.GetDat(attribute) : (TFlt) TFlt::Mn; }
*/
private:
  /*TCRef CRef;
  TInt MxNId, MxEId;
  THash<TInt, TNode> NodeH;
  THash<TInt, TEdge> EdgeH;
  /// KeyToIndexType[N|E]: Key->(Type,Index).
  TStrIntPrH KeyToIndexTypeN, KeyToIndexTypeE;

  THash<TStr, TInt> IntDefaultsN, IntDefaultsE;
  THash<TStr, TStr> StrDefaultsN, StrDefaultsE;
  THash<TStr, TFlt> FltDefaultsN, FltDefaultsE;
  TVec<TIntV> VecOfIntVecsN, VecOfIntVecsE;
  TVec<TStrV> VecOfStrVecsN, VecOfStrVecsE;
  TVec<TFltV> VecOfFltVecsN, VecOfFltVecsE;
  enum { IntType, StrType, FltType };*/
  THash<TInt, TNodeMM> NodeMMH; //The hash table for nodes TODO: Decide if this is necessary.
//  THash<<TInt, TInt>, TEdgeMM> TypeEdgeH; //(Src Type Id, EId) -> edge class
//  THash<TInt, TVec<TVec<TEdgeMM>>> NbrVVH; //A Hash table from type id to the corresponding vector of vectors
//  TVec<TVec<TIntV> > OutEdgeV;
//  TVec<TVec<TIntV> > InEdgeV;
  TInt NTypeId;
  TMMNet MMNet; //the parent MMNet

  THash<TStr, TInt> EdgeTypeToId;
public:
  //TODO: Update constructors with information from fields above.
  TMultiNet() : TNEANet(), TypeEdgeH(), OutEdgeV(), InEdgeV(), MxTypeEId(0), NTypeId(-1) { }
  TMultiNet(const int& TypeId) : TNEANet(), TypeEdgeH(), OutEdgeV(), InEdgeV(), MxTypeEId(0), NTypeId(TypeId) { }
  /// Constructor that reserves enough memory for a graph of nodes and edges.
  explicit TMultiNet(const int& Nodes, const int& Edges) : TNEANet(Nodes, Edges),
    TypeEdgeH(), OutEdgeV(), InEdgeV(), MxTypeEId(0), NTypeId(-1) { }
  explicit TMultiNet(const int& Nodes, const int& Edges, const int& TypeId) : TNEANet(Nodes, Edges),
    TypeEdgeH(), OutEdgeV(), InEdgeV(), MxTypeEId(0), NTypeId(TypeId) { }
  TMultiNet(const TMultiNet& Graph) :  TNEANet(Graph), TypeEdgeH(Graph.TypeEdgeH),
    OutEdgeV(Graph.OutEdgeV), InEdgeV(Graph.InEdgeV), MxTypeEId(Graph.MxTypeEId), NTypeId(Graph.NTypeId) { }
  /// Constructor for loading the graph from a (binary) stream SIn.
  TMultiNet(TSIn& SIn) : TNEANet(SIn), TypeEdgeH(SIn), OutEdgeV(SIn), InEdgeV(SIn), MxTypeEId(SIn), NTypeId(SIn) { }

  //Make these functions virtual

  /// Saves the graph to a (binary) stream SOut.
  void Save(TSOut& SOut) const {
    TNEANet::Save(SOut); TypeEdgeH.Save(SOut); OutEdgeV.Save(SOut);
    InEdgeV.Save(SOut); MxTypeEId.Save(SOut); NTypeId.Save(SOut); }
  /// Static cons returns pointer to graph. Ex: PMultiNet Graph=TMultiGraph::New().
  static PMultiNet New() { return PMultiNet(new TMultiNet()); }
  /// Static constructor that returns a pointer to the graph and reserves enough memory for Nodes nodes and Edges edges. ##TNEANet::New
  static PMultiNet New(const int& Nodes, const int& Edges) { return PMultiNet(new TMultiNet(Nodes, Edges)); }
  /// Static constructor that loads the graph from a stream SIn and returns a pointer to it.
  static PMultiNet Load(TSIn& SIn) { return PMultiNet(new TMultiNet(SIn)); }




//these function would just be a wrapper, that calls the TMMNet method
// private methods,
 /// Returns an ID that is larger than any edge ID in the network.
  int GetMxTypeEId() const { return MxTypeEId; }


  int DelNode ( const int& NId);

  // Returns the number of edges in the graph.
  //int GetEdges() const { return EdgeH.Len(); }
  /// Adds an edge with ID EId between node IDs SrcNId and DstNId to the graph. ##TNEANet::AddEdge

  int AddEdge(const int& SrcNId, const int& DstNId, const int& DstModeId, const TInt& EId=-1); //assume srcNId is of the current mode type
  int AddEdge(const int& NId, const int& OtherTypeNId, bool direction, const int& DstModeId, const TInt& EId=-1);
  int AddEdge(const int& NId, const int& OtherTypeNId, bool direction, const TStr& LinkTypeName, const TInt& EId=-1);
  int DelEdge(const TStr& LinkTypeName, const TInt& EId);


  //method to add neighbors; will be called by TMMNet AddEdge function; outEdge == true iff NId(which is of the type of the TMultiNet; i.e. it should refer to a node in this graph) is the source node.
  int AddNeighbor(const int& NId, const int& EId, bool outEdge);
  int DelNeighbor(const int& NId, const int& EId, bool outEdge);

  /// Adds an edge between EdgeI.GetSrcNId() and EdgeI.GetDstNId() to the graph.
  //int AddEdge(const TEdgeI& EdgeI) { return AddEdge(EdgeI.GetSrcNId(), EdgeI.GetDstNId(), EdgeI.GetId()); }
  /// Deletes an edge with edge ID EId from the graph.
//  void DelEdge(const int& EId);
  /// Adds an edge with ID EId between node IDs SrcNId and DstNId to the graph. ##TNEANet::AddEdge
//  int AddEdge(const int& SrcNId, const int& SrcNTypeId, const int& DstNId, const int& DstNTypeId, int EId=-1);
  /// Deletes an edge with edge ID EId from the graph.
//  void DelEdge(const int& EId, const TStr& EdgeType);
  /// Deletes all edges between node IDs SrcNId and DstNId from the graph. ##TNEANet::DelEdge
//  void DelEdge(const int& SrcNId, const int& SrcNTypeId, const int& DstNId, const int& DstNTypeId);
  /// Tests whether an edge with edge ID EId exists in the graph.
  //bool IsEdge(const int& EId) const { return EdgeH.IsKey(EId); }
  /// Tests whether an edge between node IDs SrcNId and DstNId exists in the graph.
  //bool IsEdge(const int& SrcNId, const int& DstNId, const bool& IsDir = true) const { int EId; return IsEdge(SrcNId, DstNId, EId, IsDir); }
  /// Tests whether an edge between node IDs SrcNId and DstNId exists in the graph. if an edge exists, return its edge ID in EId
  //bool IsEdge(const int& SrcNId, const int& DstNId, int& EId, const bool& IsDir = true) const;
  /// Returns an edge ID between node IDs SrcNId and DstNId, if such an edge exists. Otherwise, return -1.
  //int GetEId(const int& SrcNId, const int& DstNId) const { int EId; return IsEdge(SrcNId, DstNId, EId)?EId:-1; }
  /// Returns an iterator referring to the first edge in the graph.
  //TEdgeI BegEI() const { return TEdgeI(EdgeH.BegI(), this); }
  /// Returns an iterator referring to the past-the-end edge in the graph.
  //TEdgeI EndEI() const { return TEdgeI(EdgeH.EndI(), this); }
  /// Returns an iterator referring to edge with edge ID EId.
  //TEdgeI GetEI(const int& EId) const { return TEdgeI(EdgeH.GetI(EId), this); }
  /// Returns an iterator referring to edge (SrcNId, DstNId) in the graph.
  //TEdgeI GetEI(const int& SrcNId, const int& DstNId) const { return GetEI(GetEId(SrcNId, DstNId)); }

  /// Gets a vector IDs of all edges in the graph.
  //void GetEIdV(TIntV& EIdV) const;

  /// Deletes all nodes and edges from the graph.
  void Clr() { TNEANet::Clr(); TypeEdgeH.Clr(); OutEdgeV.Clr(); InEdgeV.Clr(); MxTypeEId = 0; NTypeId = -1;}

  /// Returns a small multigraph on 5 nodes and 6 edges. ##TNEANet::GetSmallGraph
  static PMultiNet GetSmallGraph();
  friend class TPt<TMultiNet>;
};

class TMultiLink;

typedef TPt<TMultiLink> PMultiLink;

//A class for each link table
//TODO: Attributes: how?
//TODO: Name this as multi link table?
class TMultiLink {

public:
  class TMultiEdge {
  private:
    TInt EId;
    TInt SrcNId, DstNId;
    TBool direction;
  public:
    TMultiEdge() : EId(-1), SrcNId(-1), DstNId(-1), direction() { }
    TMultiEdge(const int& EId, const int& SourceNId, const int& DestNId, const bool& direc) :
      Id(EId), SrcNId(SourceNId), DstNId(DestNId), direction(direc) { }
    TMultiEdge(const TMultiEdge& MultiEdge) : EId(MultiEdge.EId), SrcNId(MultiEdge.SrcNId),
        DstNId(MultiEdge.DstNId), direction(MuliEdge.direction) { }
    TMultiEdge(TSIn& SIn) : EId(SIn), SrcNId(SIn), DstNId(SIn), direction(SIn) { }
    void Save(TSOut& SOut) const { EId.Save(SOut); SrcNId.Save(SOut); DstNId.Save(SOut); direction.Save(SOut); }
    int GetId() const { return EId; }
    int GetSrcNId() const { if (direction) { return SrcNId; } else { return DstNId; } }
    int GetDstNId() const { if (direction) { return DstNId; } else { return SrcNId; } }
    bool GetDirection() const { return direction; }
    friend class TMultiLink;
  };
    /// Edge iterator. Only forward iteration (operator++) is supported.
  class TMultiEdgeI {
  private:
    typedef THash<TInt, TMultiEdge>::TIter THashIter;
    THashIter EdgeHI;
    const TMultiLink *Graph;
  public:
    TEdgeI() : EdgeHI(), Graph(NULL) { }
    TEdgeI(const THashIter& EdgeHIter, const TMultiLink *GraphPt) : EdgeHI(EdgeHIter), Graph(GraphPt) { }
    TEdgeI(const TMultiEdgeI& EdgeI) : EdgeHI(EdgeI.EdgeHI), Graph(EdgeI.Graph) { }
    TEdgeI& operator = (const TMultiEdgeI& EdgeI) { if (this!=&EdgeI) { EdgeHI=EdgeI.EdgeHI; Graph=EdgeI.Graph; }  return *this; }
    /// Increment iterator.
    TEdgeI& operator++ (int) { EdgeHI++; return *this; }
    bool operator < (const TMultiEdgeI& EdgeI) const { return EdgeHI < EdgeI.EdgeHI; }
    bool operator == (const TMultiEdgeI& EdgeI) const { return EdgeHI == EdgeI.EdgeHI; }
    /// Returns edge ID.
    int GetId() const { return EdgeHI.GetDat().GetId(); }
    /// Returns the source of the edge.
    int GetSrcNId() const { return EdgeHI.GetDat().GetSrcNId(); }
    /// Returns the destination of the edge.
    int GetDstNId() const { return EdgeHI.GetDat().GetDstNId(); }

    /// Returns the source of the edge.
    int GetSrcModeId() const { if (EdgeHI.GetDat().GetDirection()) { return Graph->GetMode1(); } else { return Graph->GetMode2(); } }
    /// Returns the destination of the edge.
    int GetDstModeId() const { if (EdgeHI.GetDat().GetDirection()) { return Graph->GetMode2(); } else { return Graph->GetMode1(); } }

    friend class TMultiLink;
  };

private:
  THash<TInt,TMultiEdge> LinkH;
  TInt MxEId;
  TInt Mode1;
  TInt Mode2;
  PMMnet Net;
  //Constructors
public:
  TMultiLink() : MxEId(-1), LinkH() {}
public:
  int AddLink (const int& sourceNId, const int& sourceNModeId, const int& destNId, const int& destNModeId, const int& EId=-1);
  int AddLink (const int& NIdType1, const int& NIdType2, const bool& direction, const int& EId=-1);
  TMultiEdgeI GetLinkI(const int& EId) const { return TMultiEdgeI(LinkH.GetI(EId), this); }
  TMultiEdgeI BegLinkI() const { return TMultiEdgeI(LinkH.BegI(), this); }
  TMultiEdgeI EndLinkI() const { return TMultiEdgeI(LinkH.EndI(), this); }
  int DelLink(const int& EId) const;
  int GetMode1() const { return Mode1; }
  int GetMode2() const { return Mode2; }
  friend class TMMNet;
};

//The container class for a multimodal network

class TMMNet {


private:
  TInt MxModeId; //The number of modes
  TInt MxLinkTypeId;
  TVec<PMultiNet> PMultiNetV; //The vector of TNEANetMM's this contains. TODO: Decide whether this is vec or hash
  TVec<TMultiLink> TMultiLinkV;

  THash<TInt,TStr> ModeIdToNameH;
  THash<TStr,TInt> ModeNameToIdH;

  THash<TInt,TStr> LinkIdToNameH;
  THash<TStr,TInt> LinkNameToIdH;

  THash<TIntPr, TStr> LinkPrToNameH;
  THash<TStr, TIntPr> LinkNameToPrH;

public:
  TMMNet() : MxModeId(0), TMultiNetV() {}
  TMMNet(const TMMNet& OtherTMMNet) : MxModeId(OtherTMMNet.MxModeId), TNEANetMMV(OtherTMMNet.TNEANetMMV) {}
  int AddMode(const TStr& ModeName, TInt& ModeId); //TODO: Implement. Decide return type.
  int DelMode(const TInt& ModeId);
  int DelMode(const TStr& ModeName);
  int AddLinkType(const TStr& ModeName1, const TStr& ModeName2, const TStr& EdgeTypeName, TInt& EdgeTypeId);
  int AddLinkType(const TInt& ModeId1, const TInt& ModeId2, const TStr& EdgeTypeName, TInt& EdgeTypeId);
  int DelLinkType(const TInt& EdgeTypeId);



  //Interface
  int GetModeId(const TStr& ModeName) const { return ModeNameToIdH.GetDat(ModeName);  }//TODO: Return type int or TInt?
  TStr GetModeName(const TInt& ModeId) const { return ModeIdToNameH.GetDat(ModeId); }

private:
  int AddEdge(const TInt& SrcNModeId, const TInt& DstNModeId, const TInt& SrcNId, const TInt& DstNId, TInt EId=-1); //TODO: Implement. Decide order of arguments.
  int AddEdge(int& NId, int& OtherTypeNId, bool& direction, TStr& LinkTypeName, TInt& EId=-1);

};

// set flags
namespace TSnap {
template <> struct IsMultiGraph<TMultiNet> { enum { Val = 1 }; };
template <> struct IsDirected<TMultiNet> { enum { Val = 1 }; };
}
#endif // NETWORKMM_H
