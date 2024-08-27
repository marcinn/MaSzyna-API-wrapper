#include <godot_cpp/classes/gd_extension.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "MaszynaTBrake.hpp"
#include "maszyna/McZapkie/hamulce.h"

namespace godot {

    void MaszynaTBrake::_bind_methods() {
        ClassDB::bind_method(D_METHOD("GetFC"), &MaszynaTBrake::GetFC);
        ClassDB::bind_method(D_METHOD("GetBCP"), &MaszynaTBrake::GetBCP);
        ClassDB::bind_method(D_METHOD("GetEDBCP"), &MaszynaTBrake::GetEDBCP);
        ClassDB::bind_method(D_METHOD("GetBRP"), &MaszynaTBrake::GetBRP);
        ClassDB::bind_method(D_METHOD("GetVRP"), &MaszynaTBrake::GetVRP);
        ClassDB::bind_method(D_METHOD("GetCRP"), &MaszynaTBrake::GetCRP);
        ClassDB::bind_method(D_METHOD("GetPF"), &MaszynaTBrake::GetPF);
        ClassDB::bind_method(D_METHOD("GetHPFlow"), &MaszynaTBrake::GetHPFlow);
        ClassDB::bind_method(D_METHOD("GetBCF"), &MaszynaTBrake::GetBCF);
    }

    // Clang-Tidy: Constructor does not initialize these fields: brakes
    MaszynaTBrake::MaszynaTBrake() {
        // move to _init or _ready signal
        initialize_brakes();
    }

    void MaszynaTBrake::initialize_brakes() {
        // ta metoda powinna byc wywolana po kazdym property change (jak juz
        // atrybuty beda mialy properties, chyba ze da sie maszynowy TBrake zmieniac z
        // zewnatrz
        this->brakes = new TBrake(i_mbp, i_bcr, i_bcd, i_brc, i_bcn, i_BD, i_mat, i_ba, i_nbpa);
        brakes->Init(PP, HPP, LPP, BP, BDF);
        UtilityFunctions::print("[MaSzyna::Brake] Brakes initialized successfully");
    }

    /**
     * @param Vel
     * @param N
     * @return Brake friction coefficient
     */
    double MaszynaTBrake::GetFC(const double Vel, const double N) const {
        return brakes->GetFC(Vel, N);
    }

    /**
     * @return Brake cylinder pressure
     */
    double MaszynaTBrake::GetBCP() const {
        return brakes->GetBCP();
    }

    /**
     * @return Electrodynamic brake control pressure
     */
    double MaszynaTBrake::GetEDBCP() const {
        return brakes->GetEDBCP();
    }

    /**
     * @return Auxiliary tank pressure
     */
    double MaszynaTBrake::GetBRP() const {
        return brakes->GetBRP();
    }

    /**
     * @return Pre-chamber pressure
     */
    double MaszynaTBrake::GetVRP() const {
        return brakes->GetVRP();
    }

    /**
     * @return Control tank pressure
     */
    double MaszynaTBrake::GetCRP() const {
        return brakes->GetCRP();
    }

    /**
     * Flow between pre-chamber and main pipe
     * @param PP
     * @param dt
     * @param Vel
     * @return
     */
    double MaszynaTBrake::GetPF(double const PP, double const dt, double const Vel) const {
        return brakes->GetPF(PP, dt, Vel);
    }

    /**
     * Flow from the supply line
     * @param HP
     * @param dt
     * @return
     */
    double MaszynaTBrake::GetHPFlow(double const HP, double const dt) const {
        return brakes->GetHPFlow(HP, dt);
    }

    /**
     * @return Piston force from the piston
     */
    double MaszynaTBrake::GetBCF() const {
        return brakes->GetBCF();
    }
} // namespace godot
