#ifndef THING_H
#define THING_H

#include <iostream>
#include <vector>
#include <map>

#include "baseclass.h"
#include "relation.h"
#include "datatypes.h"

class Thing : public BaseClass {

    // dynamic relations
    std::vector<Relation*> relations;

public:
    virtual std::string getClassName() const { return "Thing"; }

    // populate with relations
    void addRelation(Relation* t) { relations.push_back(t); }

    // removes a relation
    void removeRelation(Relation* r) {
      int i = 0;
      for (auto i : relations) {
          if (r == i) {
            break;
          }
        i += 1;
      }
      relations.erase(relations.begin()+i);
    }

    // Create a relation to this entity
    template<class T, class T0>
    void createRelationTo(T0* o1) {

        T* r = new T(this,o1);

        this->addRelation(r);
        o1->addRelation(r);
    }

    // Creates multiple relations to this entity at once
    template<class T, class T0>
    void createRelationsTo(std::vector<T0*> o1) {

      for (auto i : o1) {
        T* r = new T(this,i);

        this->addRelation(r);
        i->addRelation(r);
      }
    }

    // find a relation of a specific type
    // TODO: optimize search using multimap<std::string,Relation*>,
    //       getClassName() function for the key and a static_cast<T*>

    // Gets all the entities with given relation to this entity
    template<class T> std::vector<T*> getRelations();

    // Gets the last entity with given relation to this entity
    template<class T> T* getLastRelation();

    // Gets the all the entities with the specified class related to this entity
    template<class T>
    std::vector<T*> getRelatedObjects();

    // Gets all the entities with given relation to the entity, but automatically return its scalar value
    template<class T>
    std::vector<double> getRelatedScalarObjects();

    // Gets all the entities with given relation to the entity, but automatically return its vector value
    template<class T>
    std::vector<std::vector<double>> getRelatedVectorObjects();
};

class Item : public Thing {
public:
    std::string getClassName() const { return "Item"; }
};

class Collection : public Thing {
public:
    std::string getClassName() const { return "Collection"; }
};

class Physical : public Item {
public:
    std::string getClassName() const { return "Physical"; }
};

class Quantum : public Item {
public:
    std::string getClassName() const { return "Quantum"; }
};

class Void : public Item {
public:
    std::string getClassName() const { return "Void"; }
};

class Elementary : public Physical {
public:
    std::string getClassName() const { return "Elementary"; }
};

class Perspective : public Physical {
public:
    std::string getClassName() const { return "Perspective"; }
};

class Symbolic : public Perspective {
public:
    std::string getClassName() const { return "Symbolic"; }
};

class String : public Symbolic, public DataType<std::string>
{
public:
    std::string getClassName() const { return "String"; }
};

class Vector : public Symbolic, public DataType<std::vector<double>>
{
public:
    Vector(std::vector<double> s) {data = s;}
    std::string getClassName() const { return "Vector"; }
};

class IUPAC : public String
{
public:
    IUPAC(std::string _iupac) { data = _iupac; }
    std::string getClassName() const { return "IUPAC Name"; }
};

class LatexExpression : public String
{
public:
  LatexExpression(std::string _expr) { data = _expr; }
  std::string getClassName() const { return "LatexExpression"; }
};

class Unit : public String
{
public:
    Unit(std::string _unit) {data = _unit;}
    std::string getClassName() const { return "Unit"; }
};

class Quantity : public Symbolic
{
public:
    std::string getClassName() const { return "Quantity"; }
};

class Scalar : public Symbolic, public DataType<double>
{
public:
    Scalar(double s) {data = s;}
    std::string getClassName() const { return "Scalar"; }
};

class ScalarQuantity : public Quantity
{
public:
    ScalarQuantity(Scalar* _s, Unit* _u)
    {
        createRelationsTo<hasPart,Thing>({_u,_s});
    }

    std::string getClassName() const { return "ScalarQuantity"; }
};

class Pressure : public ScalarQuantity
{
public:
    Pressure(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "Pressure"; }
};

class PressureTimeDerivative : public ScalarQuantity
{
public:
    PressureTimeDerivative(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "PressureTimeDerivative"; }
};

class Temperature : public ScalarQuantity
{
public:
    Temperature(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "Temperature"; }
};

class TemperatureTimeDerivative : public ScalarQuantity
{
public:
    TemperatureTimeDerivative(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "TemperatureTimeDerivative"; }
};

class MolarFraction : public ScalarQuantity
{
public:
    MolarFraction(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "MolarFraction"; }
};

class Mass : public ScalarQuantity
{
public:
    Mass(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "Mass"; }
};

class BulkDensityLiquid : public ScalarQuantity
{
public:
    BulkDensityLiquid(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "BulkDensityLiquid"; }
};

class BulkDensitySolid : public ScalarQuantity
{
public:
    BulkDensitySolid(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "BulkDensitySolid"; }
};

class MeltingPoint : public ScalarQuantity
{
public:
    MeltingPoint(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "MeltingPoint"; }
};

class Viscosity : public ScalarQuantity
{
public:
    Viscosity(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "Viscosity"; }
};

class VectorQuantity : public Quantity
{
public:
    VectorQuantity(Vector* _s, Unit* _u)
    {
        createRelationsTo<hasPart,Thing>({_u,_s});
    }

    std::string getClassName() const { return "VectorQuantity"; }
};

class SurfaceTension : public ScalarQuantity
{
public:
    SurfaceTension(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "SurfaceTension"; }
};

class SaturationPressure : public ScalarQuantity
{
public:
    SaturationPressure(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "SaturationPressure"; }
};

class KnowledgeGenerator : virtual public Perspective {
public:
    std::string getClassName() const { return "KnowledgeGenerator"; }
};

class Model : virtual public Perspective {
public:
    std::string getClassName() const { return "Model"; }
};

class SoftwareModel : public Model, public KnowledgeGenerator {
public:
    std::string getClassName() const { return "SoftwareModel"; }
};

class MathematicalModel : public Model {
public:

    MathematicalModel (std::string _expr) : Model() {

    this->createRelationTo<hasProperty,LatexExpression>(new LatexExpression(_expr));
    }

    std::string getClassName() const { return "MathematicalModel"; }
};

class PhysicsBasedModel : public MathematicalModel {
public:
    PhysicsBasedModel(std::string _expr) : MathematicalModel(_expr) {

      this->createRelationTo<hasProperty,LatexExpression>(new LatexExpression(_expr));
      }
    std::string getClassName() const { return "PhysicsBasedModel"; }
};

class ContinuumModel : public PhysicsBasedModel {
public:
    ContinuumModel(std::string _expr) : PhysicsBasedModel(_expr) {

      this->createRelationTo<hasProperty,LatexExpression>(new LatexExpression(_expr));
      }
    std::string getClassName() const { return "ContinuumModel"; }
};

class MesoscopicModel : public PhysicsBasedModel {
public:
    MesoscopicModel(std::string _expr) : PhysicsBasedModel(_expr) {

      this->createRelationTo<hasProperty,LatexExpression>(new LatexExpression(_expr));
      }
    std::string getClassName() const { return "MesoscopicModel"; }
};

class Reductionistic : public Perspective {
public:
    std::string getClassName() const { return "Reductionistic"; }
};

class Existent : public Reductionistic {
public:
    std::string getClassName() const { return "Existent"; }
};

class State : public Existent {
public:
    std::string getClassName() const { return "State"; }
};

class Matter : public Perspective {
public:
    std::string getClassName() const { return "Matter"; }
};

class Continuum : public Matter {
public:
    std::string getClassName() const { return "Continuum"; }
};

class Fluid : public Continuum {
public:
    std::string getClassName() const { return "Fluid"; }
};

class Gas : public Fluid {
public:
    std::string getClassName() const { return "Gas"; }
};

class GasMixture : public Gas {
public:
    std::string getClassName() const { return "GasMixture"; }
};

class MolecularEntity : public Matter {
public:
    std::string getClassName() const { return "MolecularEntity"; }
};

class Atom : public MolecularEntity {
public:
    std::string getClassName() const { return "Atom"; }
};

class PolyatomicEntity : public MolecularEntity {
public:
    std::string getClassName() const { return "PolyatomicEntity"; }
};

class HeteronuclearMolecule : public PolyatomicEntity {
public:
    std::string getClassName() const { return "HeteronuclearMolecule"; }
};

class HomonuclearMolecule : public PolyatomicEntity {
public:
    std::string getClassName() const { return "HomonuclearMolecule"; }
};

class Time : public ScalarQuantity {
public:
    Time(Scalar* _s, Unit* _u) : ScalarQuantity(_s,_u) {}

    std::string getClassName() const { return "Time"; }
};

#include "thing.cpp"

#endif // THING_H
