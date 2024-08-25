#include "maszyna.h"

#include <godot_cpp/classes/gd_extension.hpp>
#include "hamulce.h"
#include <godot_cpp/variant/utility_functions.hpp>

namespace Maszyna {
    void Api::_bind_methods() {

    }


    namespace Brakes {
        TBrake *brakes = nullptr;

        void Brake::_bind_methods() {
            godot::ClassDB::bind_static_method("Brake", godot::D_METHOD("init_brake"), &Brake::Init);
            godot::ClassDB::bind_static_method("Brake", godot::D_METHOD("get_fc"), &Brake::GetFC);
            godot::ClassDB::bind_static_method("Brake", godot::D_METHOD("get_bcp"), &Brake::GetBCP);
            godot::ClassDB::bind_static_method("Brake", godot::D_METHOD("get_edbcp"), &Brake::GetEDBCP);
            godot::ClassDB::bind_static_method("Brake", godot::D_METHOD("get_brp"), &Brake::GetBRP);
            godot::ClassDB::bind_static_method("Brake", godot::D_METHOD("get_vrp"), &Brake::GetVRP);
            godot::ClassDB::bind_static_method("Brake", godot::D_METHOD("get_crp"), &Brake::GetCRP);
            godot::ClassDB::bind_static_method("Brake", godot::D_METHOD("get_pf"), &Brake::GetPF);
            godot::ClassDB::bind_static_method("Brake", godot::D_METHOD("get_hpflow"), &Brake::GetHPFlow);
            godot::ClassDB::bind_static_method("Brake", godot::D_METHOD("get_bcf"), &Brake::GetBCF);
        }

        /**
         * Are the docs working? If so, implement damn error handling! GDExtension does not allow the class constructor with parameters
         * @param PP 
         * @param HPP 
         * @param LPP 
         * @param BP 
         * @param BDF 
         * @param i_mbp 
         * @param i_bcr 
         * @param i_bcd 
         * @param i_brc 
         * @param i_bcn 
         * @param i_BD 
         * @param i_mat 
         * @param i_ba 
         * @param i_nbpa 
         */
        void Brake::Init(const double PP, const double HPP, const double LPP, const double BP, const int BDF,
                         const double i_mbp, const double i_bcr, const double i_bcd, const double i_brc, const int i_bcn,
                         const int i_BD, const int i_mat, const int i_ba, const int i_nbpa) {
            brakes = new TBrake(i_mbp, i_bcr, i_bcd, i_brc, i_bcn, i_BD, i_mat, i_ba, i_nbpa);
            brakes->Init(PP, HPP, LPP, BP, BDF);
            godot::UtilityFunctions::print("[MaSzyna::Brake] Brakes initialized successfully");
        }

        /**
         * @param Vel
         * @param N
         * @return Brake friction coefficient
         */
        double Brake::GetFC(const double Vel, const double N) {
            return brakes->GetFC(Vel, N);
        }

        /**
         * @return Brake cylinder pressure
         */
        double Brake::GetBCP() {
            return brakes->GetBCP();
        }

        /**
         * @return Electrodynamic brake control pressure
         */
        double Brake::GetEDBCP() {
            return brakes->GetEDBCP();
        }

        /**
         * @return Auxiliary tank pressure
         */
        double Brake::GetBRP() {
            return brakes->GetBRP();
        }

        /**
         * @return Pre-chamber pressure
         */
        double Brake::GetVRP() {
            return brakes->GetVRP();
        }

        /**
         * @return Control tank pressure
         */
        double Brake::GetCRP() {
            return brakes->GetCRP();
        }

        /**
         * Flow between pre-chamber and main pipe
         * @param PP 
         * @param dt 
         * @param Vel 
         * @return 
         */
        double Brake::GetPF(double const PP, double const dt, double const Vel) {
            return brakes->GetPF(PP, dt, Vel);
        }

        /**
         * Flow from the supply line
         * @param HP
         * @param dt
         * @return
         */
        double Brake::GetHPFlow(double const HP, double const dt) {
            return brakes->GetHPFlow(HP, dt);
        }

        /**
         * @return Piston force from the piston
         */
        double Brake::GetBCF() {
            return brakes->GetBCF();
        }
    }

}
