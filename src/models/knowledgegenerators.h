#ifndef KNOWLEDGEGENERATORS_H
#define KNOWLEDGEGENERATORS_H

#include <boost/any.hpp>
#include <boost/foreach.hpp>


#include "surfacetensionmodels/surfacetensionmodel.h"
#include "saturationpressuremodels/saturationpressuremodel.h"
//#include "gasmodels/gasmodel.h"
//#include "gasmodels/gasmodelcv.h"
//#include "nanomodels/nucleation/cnt.h"
//#include "nanomodels/moments/momentmodelpratsinis.h"
//#include "statemodels/stateinterpolator.h"

class KnowledgeGeneratorsDB {
protected:
  std::vector<Thing*> list;

public:
  // Constructo
  KnowledgeGeneratorsDB() {
    // KnowledgeGenerators must be added manually by the developer
    list.push_back(new SaturationPressureModel);
    list.push_back(new SurfaceTensionModel);
  }

  // search for knowledge generators which are model for the given entity
  auto ismodelfor (Thing* criteria) {
//  auto ismodelfor (std::string criteria) {
    std::vector<std::string> champions;

    for (auto i : list) {
      auto mod_for = i->getRelations<isModelFor>();
      for (auto ii : mod_for) {
        auto modeled = ii->getRange()->getClassName();
        if (modeled == criteria->getClassName())  {
//        if (modeled == criteria)  {
          champions.push_back(i->getClassName());
        }
      }
    }
    return champions;
  }

};

#endif // KNOWLEDGEGENERATORS_H
