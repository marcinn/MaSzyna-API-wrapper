//
// Created by karol on 25.08.2024.
//

#ifndef MASZYNA_H
#define MASZYNA_H
#include <godot_cpp/classes/node.hpp>
#include "maszyna/McZapkie/hamulce.h"

namespace godot {
    /**
     * Test
     */
    class MaszynaTBrake : public Node {
        GDCLASS(MaszynaTBrake, Node)

        private:
            Maszyna::TBrake *brakes;

            double PP = 0.0;
            double HPP=0.0;
            double LPP=0.0;
            double BP=0.0;
            int BDF=0;
            double i_mbp=0.0;
            double i_bcr=0.0;
            double i_bcd=0.0;
            double i_brc=0.0;
            int i_bcn = 0;
            int i_BD = 0;
            int i_mat = 0;
            int i_ba = 0;
            int i_nbpa = 0;

        public:
            void initialize_brakes();
            static void _bind_methods();

            double GetFC(double Vel, double N);
            double GetBCP();
            double GetEDBCP();
            double GetBRP();
            double GetVRP();
            double GetCRP();
            double GetPF(double PP, double dt, double Vel);
            double GetHPFlow(double HP, double dt);
            double GetBCF();

            MaszynaTBrake();
            ~MaszynaTBrake() override = default;
    };
}

#endif //MASZYNA_H
