/* This file is part of the Palabos library.
 *
 * The Palabos softare is developed since 2011 by FlowKit-Numeca Group Sarl
 * (Switzerland) and the University of Geneva (Switzerland), which jointly
 * own the IP rights for most of the code base. Since October 2019, the
 * Palabos project is maintained by the University of Geneva and accepts
 * source code contributions from the community.
 * 
 * Contact:
 * Jonas Latt
 * Computer Science Department
 * University of Geneva
 * 7 Route de Drize
 * 1227 Carouge, Switzerland
 * jonas.latt@unige.ch
 *
 * The most recent release of Palabos can be downloaded at 
 * <https://palabos.unige.ch/>
 *
 * The library Palabos is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * The library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/** \file
 * Helper functions for the implementation of LB dynamics. This file is all
 * about efficiency. The generic template code is specialized for commonly
 * used Lattices, so that a maximum performance can be taken out of each
 * case.
 * Theoretical background about these collision models can be found in
 * Coreixas et al. 'Comprehensive comparison of collision models in the 
 * lattice Boltzmann framework: Theoretical investigations', PRE, 2019.
 */
#ifndef COMPREHENSIVE_MODELS_TEMPLATES_H
#define COMPREHENSIVE_MODELS_TEMPLATES_H

#include "core/globalDefs.h"
#include "core/cell.h"
#include "core/util.h"
#include "latticeBoltzmann/offEquilibriumTemplates.h"

namespace plb {

template<typename T, class Descriptor> struct comprehensiveDynamicsTemplatesImpl;

/// Implementation of all collision terms in the article Christophe Coreixas et al.
/// "Comprehensive comparison of collision models in the lattice Boltzmann framework: Theoretical investigations."
template<typename T, template<typename U> class Descriptor>
struct comprehensiveDynamicsTemplates {

//========================= RM = Raw Moments ======================//
static void RMcomputeMoments(Cell<T,Descriptor> const& cell, Array<T, Descriptor<T>::q>& RM, T& rho)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::RMcomputeMoments(cell.getRawPopulations(), RM, rho);
}

static void RMcomputeEquilibriumMoments(T rho, Array<T,Descriptor<T>::d> const& u, Array<T, Descriptor<T>::q>& RMeq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::RMcomputeEquilibriumMoments(rho, u, RMeq);
}

static void RMcomputeEquilibrium(T rho, Array<T, Descriptor<T>::q> const& RMeq, Array<T, Descriptor<T>::q>& eq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::RMcomputeEquilibrium(rho, RMeq, eq);
}

static void RMcollide(Cell<T,Descriptor>& cell, T rho, Array<T, Descriptor<T>::d> const& u,
                      Array<T, Descriptor<T>::q> const& RM,    // Raw moments
                      Array<T, Descriptor<T>::q> const& RMeq,  // Equilibrium moments (raw)
                      Array<T, Descriptor<T>::numRelaxationTimes> const& omega)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::RMcollide(cell.getRawPopulations(), rho, u, RM, RMeq, omega);
}

//========================= HM = Hermite Moments ======================//
static void HMcomputeMoments(Cell<T,Descriptor> const& cell, Array<T, Descriptor<T>::q>& HM, T& rho)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::HMcomputeMoments(cell.getRawPopulations(), HM, rho);
}

static void HMcomputeEquilibriumMoments(T rho, Array<T,Descriptor<T>::d> const& u, Array<T, Descriptor<T>::q>& HMeq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::HMcomputeEquilibriumMoments(rho, u, HMeq);
}

static void HMcomputeEquilibrium(T rho, Array<T, Descriptor<T>::q> const& HMeq, Array<T, Descriptor<T>::q>& eq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::HMcomputeEquilibrium(rho, HMeq, eq);
}

static void HMcollide(Cell<T,Descriptor>& cell, T rho, Array<T, Descriptor<T>::d> const& u,
                      Array<T, Descriptor<T>::q> const& HM,    // Hermite moments
                      Array<T, Descriptor<T>::q> const& HMeq,  // Equilibrium moments (hermite)
                      Array<T, Descriptor<T>::numRelaxationTimes> const& omega)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::HMcollide(cell.getRawPopulations(), rho, u, HM, HMeq, omega);
}


//========================= CM = Central Moments ======================//
static void CMcomputeMoments(Cell<T,Descriptor> const& cell, Array<T, Descriptor<T>::q>& CM, T& rho, Array<T,Descriptor<T>::d>& u)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::CMcomputeMoments(cell.getRawPopulations(), CM, rho, u);
}

static void CMcomputeEquilibriumMoments(Array<T, Descriptor<T>::q>& CMeq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::CMcomputeEquilibriumMoments(CMeq);
}
static void CMcomputeEquilibrium(T rho, Array<T,Descriptor<T>::d> const& u, Array<T, Descriptor<T>::q> const& CMeq, Array<T, Descriptor<T>::q>& eq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::CMcomputeEquilibrium(rho, u, CMeq, eq);
}

static void CMcollide(Cell<T,Descriptor>& cell, T rho, Array<T, Descriptor<T>::d> const& u,
                      Array<T, Descriptor<T>::q> const& CM,    // Central moments
                      Array<T, Descriptor<T>::q> const& CMeq,  // Equilibrium moments (central)
                      Array<T, Descriptor<T>::numRelaxationTimes> const& omega)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::CMcollide(cell.getRawPopulations(), rho, u, CM, CMeq, omega);
}


//========================= CHM = Central Hermite Moments ======================//
static void CHMcomputeMoments(Cell<T,Descriptor> const& cell, Array<T, Descriptor<T>::q>& CHM, T& rho, Array<T,Descriptor<T>::d>& u)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::CHMcomputeMoments(cell.getRawPopulations(), CHM, rho, u);
}

static void CHMcomputeEquilibriumMoments(Array<T, Descriptor<T>::q>& CHMeq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::CHMcomputeEquilibriumMoments(CHMeq);
}
static void CHMcomputeEquilibrium(T rho, Array<T,Descriptor<T>::d> const& u, Array<T, Descriptor<T>::q> const& CHMeq, Array<T, Descriptor<T>::q>& eq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::CHMcomputeEquilibrium(rho, u, CHMeq, eq);
}

static void CHMcollide(Cell<T,Descriptor>& cell, T rho, Array<T, Descriptor<T>::d> const& u,
                      Array<T, Descriptor<T>::q> const& CHM,    // Central Hermite moments
                      Array<T, Descriptor<T>::q> const& CHMeq,  // Equilibrium moments (central hermite)
                      Array<T, Descriptor<T>::numRelaxationTimes> const& omega)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::CHMcollide(cell.getRawPopulations(), rho, u, CHM, CHMeq, omega);
}


//========================= K = Cumulants ======================//
static void KcomputeMoments(Cell<T,Descriptor> const& cell, Array<T, Descriptor<T>::q>& K, T& rho, Array<T,Descriptor<T>::d>& u)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::KcomputeMoments(cell.getRawPopulations(), K, rho, u);
}

static void KcomputeEquilibriumMoments(Array<T, Descriptor<T>::q>& Keq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::KcomputeEquilibriumMoments(Keq);
}
static void KcomputeEquilibrium(T rho, Array<T,Descriptor<T>::d> const& u, Array<T, Descriptor<T>::q> const& Keq, Array<T, Descriptor<T>::q>& eq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::KcomputeEquilibrium(rho, u, Keq, eq);
}

static void Kcollide(Cell<T,Descriptor>& cell, T rho, Array<T, Descriptor<T>::d> const& u,
                      Array<T, Descriptor<T>::q> const& K,    // Cumulants
                      Array<T, Descriptor<T>::q> const& Keq,  // Equilibrium moments (cumulants)
                      Array<T, Descriptor<T>::numRelaxationTimes> const& omega)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::Kcollide(cell.getRawPopulations(), rho, u, K, Keq, omega);
}


//========================= GH = Gauss-Hermite Formalism (still Hermite moments) ======================//
static void GHcomputeMoments(Cell<T,Descriptor> const& cell, Array<T, Descriptor<T>::q>& GH, T& rho)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::GHcomputeMoments(cell.getRawPopulations(), GH, rho);
}

static void GHcomputeEquilibriumMoments(T rho, Array<T,Descriptor<T>::d> const& u, Array<T, Descriptor<T>::q>& GHeq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::GHcomputeEquilibriumMoments(rho, u, GHeq);
}

static void GHcomputeEquilibrium(T rho, Array<T, Descriptor<T>::q> const& GHeq, Array<T, Descriptor<T>::q>& eq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::GHcomputeEquilibrium(rho, GHeq, eq);
}

static void GHcollide(Cell<T,Descriptor>& cell, T rho, Array<T, Descriptor<T>::d> const& u,
                      Array<T, Descriptor<T>::q> const& GH,    // Hermite moments
                      Array<T, Descriptor<T>::q> const& GHeq,  // Equilibrium moments (hermite)
                      Array<T, Descriptor<T>::numRelaxationTimes> const& omega)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::GHcollide(cell.getRawPopulations(), rho, u, GH, GHeq, omega);
}


//========================= RR = Recursive Regularization based on Gauss-Hermite Formalism ======================//
static void RRcomputeMoments(Cell<T,Descriptor> const& cell, Array<T, Descriptor<T>::q>& GH, T& rho)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::RRcomputeMoments(cell.getRawPopulations(), GH, rho);
}

static void RRcomputeEquilibriumMoments(T rho, Array<T,Descriptor<T>::d> const& u, Array<T, Descriptor<T>::q>& GHeq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::RRcomputeEquilibriumMoments(rho, u, GHeq);
}

static void RRcomputeEquilibrium(T rho, Array<T, Descriptor<T>::q> const& GHeq, Array<T, Descriptor<T>::q>& eq)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::RRcomputeEquilibrium(rho, GHeq, eq);
}

static void RRcollide(Cell<T,Descriptor>& cell, T rho, Array<T, Descriptor<T>::d> const& u,
                      Array<T, Descriptor<T>::q> const& GH,    // Hermite moments
                      Array<T, Descriptor<T>::q> const& GHeq,  // Equilibrium moments (hermite)
                      Array<T, Descriptor<T>::numRelaxationTimes> const& omega)
{
    comprehensiveDynamicsTemplatesImpl<T, typename Descriptor<T>::BaseDescriptor>
        ::RRcollide(cell.getRawPopulations(), rho, u, GH, GHeq, omega);
}



};

template<typename T, class Descriptor>
struct comprehensiveDynamicsTemplatesImpl {

//========================= RM = Raw Moments ======================//
static void RMcomputeMoments([[maybe_unused]] Array<T,Descriptor::q> const& cell, [[maybe_unused]] Array<T, Descriptor::q>& RM, [[maybe_unused]] T& rho)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void RMcomputeEquilibriumMoments([[maybe_unused]] T rho, [[maybe_unused]] Array<T,Descriptor::d> const& u, [[maybe_unused]] Array<T, Descriptor::q>& RMeq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void RMcomputeEquilibrium([[maybe_unused]] T rho, [[maybe_unused]] Array<T, Descriptor::q> const& RMeq, [[maybe_unused]] Array<T, Descriptor::q>& eq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void RMcollide([[maybe_unused]] Array<T,Descriptor::q>& cell, [[maybe_unused]] T rho, [[maybe_unused]] Array<T, Descriptor::d> const& u,
                      [[maybe_unused]] Array<T, Descriptor::q> const& RM,    // Raw moments
                      [[maybe_unused]] Array<T, Descriptor::q> const& RMeq,  // Equilibrium moments (raw)
                      [[maybe_unused]] Array<T, Descriptor::numRelaxationTimes> const& omega)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

//========================= HM = Hermite Moments ======================//
static void HMcomputeMoments([[maybe_unused]] Array<T,Descriptor::q> const& cell, [[maybe_unused]] Array<T, Descriptor::q>& HM, [[maybe_unused]] T& rho)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void HMcomputeEquilibriumMoments([[maybe_unused]] T rho, [[maybe_unused]] Array<T,Descriptor::d> const& u, [[maybe_unused]] Array<T, Descriptor::q>& HMeq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void HMcomputeEquilibrium([[maybe_unused]] T rho, [[maybe_unused]] Array<T, Descriptor::q> const& HMeq, [[maybe_unused]] Array<T, Descriptor::q>& eq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void HMcollide([[maybe_unused]] Array<T,Descriptor::q>& cell, [[maybe_unused]] T rho, [[maybe_unused]] Array<T, Descriptor::d> const& u,
                      [[maybe_unused]] Array<T, Descriptor::q> const& HM,    // Hermite moments
                      [[maybe_unused]] Array<T, Descriptor::q> const& HMeq,  // Equilibrium moments (hermite)
                      [[maybe_unused]] Array<T, Descriptor::numRelaxationTimes> const& omega)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

//========================= CM = Central Moments ======================//
static void CMcomputeMoments([[maybe_unused]] Array<T,Descriptor::q> const& cell, [[maybe_unused]] Array<T, Descriptor::q>& CM, [[maybe_unused]] T& rho, [[maybe_unused]] Array<T,Descriptor::d>& u)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void CMcomputeEquilibriumMoments([[maybe_unused]] Array<T, Descriptor::q>& CMeq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void CMcomputeEquilibrium([[maybe_unused]] T rho, [[maybe_unused]] Array<T,Descriptor::d>& u, [[maybe_unused]] Array<T, Descriptor::q> const& CMeq, [[maybe_unused]] Array<T, Descriptor::q>& eq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void CMcollide([[maybe_unused]] Array<T,Descriptor::q>& cell, [[maybe_unused]] T rho, [[maybe_unused]] Array<T, Descriptor::d> const& u,
                      [[maybe_unused]] Array<T, Descriptor::q> const& CM,    // Central moments
                      [[maybe_unused]] Array<T, Descriptor::q> const& CMeq,  // Equilibrium moments (central)
                      [[maybe_unused]] Array<T, Descriptor::numRelaxationTimes> const& omega)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}


//========================= CHM = Central Hermite Moments ======================//
static void CHMcomputeMoments([[maybe_unused]] Array<T,Descriptor::q> const& cell, [[maybe_unused]] Array<T, Descriptor::q>& CHM, [[maybe_unused]] T& rho, [[maybe_unused]] Array<T,Descriptor::d>& u)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void CHMcomputeEquilibriumMoments([[maybe_unused]] Array<T, Descriptor::q>& CHMeq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void CHMcomputeEquilibrium([[maybe_unused]] T rho, [[maybe_unused]] Array<T,Descriptor::d>& u, [[maybe_unused]] Array<T, Descriptor::q> const& CHMeq, [[maybe_unused]] Array<T, Descriptor::q>& eq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void CHMcollide([[maybe_unused]] Array<T,Descriptor::q>& cell, [[maybe_unused]] T rho, [[maybe_unused]] Array<T, Descriptor::d> const& u,
                       [[maybe_unused]] Array<T, Descriptor::q> const& CHM,    // Central Hermite moments
                       [[maybe_unused]] Array<T, Descriptor::q> const& CHMeq,  // Equilibrium moments (central hermite)
                       [[maybe_unused]] Array<T, Descriptor::numRelaxationTimes> const& omega)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

//========================= K = Cumulants ======================//
static void KcomputeMoments([[maybe_unused]] Array<T,Descriptor::q> const& cell, [[maybe_unused]] Array<T, Descriptor::q>& K, [[maybe_unused]] T& rho, [[maybe_unused]] Array<T,Descriptor::d>& u)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void KcomputeEquilibriumMoments([[maybe_unused]] Array<T, Descriptor::q>& Keq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void KcomputeEquilibrium([[maybe_unused]] T rho, [[maybe_unused]] Array<T,Descriptor::d>& u, [[maybe_unused]] Array<T, Descriptor::q> const& Keq, [[maybe_unused]] Array<T, Descriptor::q>& eq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void Kcollide([[maybe_unused]] Array<T,Descriptor::q>& cell, [[maybe_unused]] T rho, [[maybe_unused]] Array<T, Descriptor::d> const& u,
                      [[maybe_unused]] Array<T, Descriptor::q> const& K,    // Central moments
                      [[maybe_unused]] Array<T, Descriptor::q> const& Keq,  // Equilibrium moments (central)
                      [[maybe_unused]] Array<T, Descriptor::numRelaxationTimes> const& omega)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}


//========================= GH = Gauss-Hermite Formalism (still Hermite moments) ======================//
static void GHcomputeMoments([[maybe_unused]] Array<T,Descriptor::q> const& cell, [[maybe_unused]] Array<T, Descriptor::q>& GH, [[maybe_unused]] T& rho)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void GHcomputeEquilibriumMoments([[maybe_unused]] T rho, [[maybe_unused]] Array<T,Descriptor::d> const& u, [[maybe_unused]] Array<T, Descriptor::q>& GHeq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void GHcomputeEquilibrium([[maybe_unused]] T rho, [[maybe_unused]] Array<T, Descriptor::q> const& GHeq, [[maybe_unused]] Array<T, Descriptor::q>& eq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void GHcollide([[maybe_unused]] Array<T,Descriptor::q>& cell, [[maybe_unused]] T rho, [[maybe_unused]] Array<T, Descriptor::d> const& u,
                      [[maybe_unused]] Array<T, Descriptor::q> const& GH,    // Hermite moments
                      [[maybe_unused]] Array<T, Descriptor::q> const& GHeq,  // Equilibrium moments (hermite)
                      [[maybe_unused]] Array<T, Descriptor::numRelaxationTimes> const& omega)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}


//========================= RR = Recursive Regularization based on Gauss-Hermite Formalism ======================//
static void RRcomputeMoments([[maybe_unused]] Array<T,Descriptor::q> const& cell, [[maybe_unused]] Array<T, Descriptor::q>& GH, [[maybe_unused]] T& rho)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void RRcomputeEquilibriumMoments([[maybe_unused]] T rho, [[maybe_unused]] Array<T,Descriptor::d> const& u, [[maybe_unused]] Array<T, Descriptor::q>& GHeq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void RRcomputeEquilibrium([[maybe_unused]] T rho, [[maybe_unused]] Array<T, Descriptor::q> const& GHeq, [[maybe_unused]] Array<T, Descriptor::q>& eq)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}

static void RRcollide([[maybe_unused]] Array<T,Descriptor::q>& cell, [[maybe_unused]] T rho, [[maybe_unused]] Array<T, Descriptor::d> const& u,
                      [[maybe_unused]] Array<T, Descriptor::q> const& GH,    // Hermite moments
                      [[maybe_unused]] Array<T, Descriptor::q> const& GHeq,  // Equilibrium moments (hermite)
                      [[maybe_unused]] Array<T, Descriptor::numRelaxationTimes> const& omega)
{
    // We only provide specialized implementations.
    PLB_ASSERT( false );
}


}; // struct comprehensiveDynamicsTemplatesImpl

}  // namespace plb

#include "latticeBoltzmann/comprehensiveModelsTemplates2D.h"

#endif  // COMPREHENSIVE_MODELS_TEMPLATES_H

