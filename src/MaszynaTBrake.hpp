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

            TBrake *brakes;

            double PP = 0.0;
            double HPP = 0.0;
            double LPP = 0.0;
            double BP = 0.0;
            int BDF = 0;
            double i_mbp = 0.0;
            double i_bcr = 0.0;
            double i_bcd = 0.0;
            double i_brc = 0.0;
            int i_bcn = 0;
            int i_BD = 0;
            int i_mat = 0;
            int i_ba = 0;
            int i_nbpa = 0;

        public:
            void initialize_brakes();
            static void _bind_methods();

            double GetFC(double Vel, double N) const;
            double GetBCP() const;
            double GetEDBCP() const;
            double GetBRP() const;
            double GetVRP() const;
            double GetCRP() const;
            double GetPF(double PP, double dt, double Vel) const;
            double GetHPFlow(double HP, double dt) const;
            double GetBCF() const;

            MaszynaTBrake();
            ~MaszynaTBrake() override = default;
    };
} // namespace godot

#endif // MASZYNA_H
