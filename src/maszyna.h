//
// Created by karol on 25.08.2024.
//

#ifndef MASZYNA_H
#define MASZYNA_H
#include <godot_cpp/classes/node.hpp>

namespace Maszyna {
    class Api final : public godot::Node {
        GDCLASS(Api, godot::Node)

    protected:
        static void _bind_methods();

    public:
        Api() = default;

        ~Api() override = default;
    };

    namespace Brakes {
        /**
         * Test
         */
        class Brake final : public godot::Node {
            GDCLASS(Brake, godot::Node)

        protected:
            static void _bind_methods();

        public:
            /**
             * Maksymalne ciśnienie, prominent, skok roboczy, pojemności ZP, files cylindrowy, opóźnienia hamulca, material klocków, osie hamowane, klocki na oś;
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
            static void Init(double PP, double HPP, double LPP, double BP, int BDF, double i_mbp, double i_bcr, double i_bcd, double i_brc, int
                             i_bcn, int i_BD, int i_mat, int i_ba, int i_nbpa);

            static double GetFC(double Vel, double N);

            static double GetBCP();

            static double GetEDBCP();

            static double GetBRP();

            static double GetVRP();

            static double GetCRP();

            static double GetPF(double PP, double dt, double Vel);

            static double GetHPFlow(double HP, double dt);

            static double GetBCF();

            Brake() = default;

            ~Brake() override = default;
        };
    }
}

#endif //MASZYNA_H
