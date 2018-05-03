#include <sstream>
#include <string>

std::string defmapstring("|-----------------------------------------------------------------------------|\n"
"|                                                                             |\n"
"| |--------------------------|        |-----------------------|               |\n"
"| |..........................|        |.......................|               |\n"
"| |..........................+########+.......................|-------|       |\n"
"| |..........................|   #    |...............................|--|    |\n"
"| |..........................|   #    |..................................|--| |\n"
"| |----------+---------------|   #    |----+----------------|...............| |\n"
"|            #                 #############                |...............| |\n"
"|            #                 #     |-----+------|         |...............| |\n"
"|            #                 #     |............|         |...............| |\n"
"|            ###################     |............|   ######+...............| |\n"
"|            #                 #     |............|   #     |...............| |\n"
"|            #                 #     |-----+------|   #     |--------+------| |\n"
"|  |---------+-----------|     #           #          #              #        |\n"
"|  |.....................|     #           #          #         |----+------| |\n"
"|  |.....................|     ########################         |...........| |\n"
"|  |.....................|     #           #                    |...........| |\n"
"|  |.....................|     #    |------+--------------------|...........| |\n"
"|  |.....................|     #    |.......................................| |\n"
"|  |.....................+##########+.......................................| |\n"
"|  |.....................|          |.......................................| |\n"
"|  |---------------------|          |---------------------------------------| |\n"
"|                                                                             |\n"
"|-----------------------------------------------------------------------------|\n"
"|-----------------------------------------------------------------------------|\n"
"|                                                                             |\n"
"| |--------------------------|        |-----------------------|               |\n"
"| |..........................|        |.......................|               |\n"
"| |..........................+########+.......................|-------|       |\n"
"| |..........................|   #    |...............................|--|    |\n"
"| |..........................|   #    |..................................|--| |\n"
"| |----------+---------------|   #    |----+----------------|...............| |\n"
"|            #                 #############                |...............| |\n"
"|            #                 #     |-----+------|         |...............| |\n"
"|            #                 #     |............|         |...............| |\n"
"|            ###################     |............|   ######+...............| |\n"
"|            #                 #     |............|   #     |...............| |\n"
"|            #                 #     |-----+------|   #     |--------+------| |\n"
"|  |---------+-----------|     #           #          #              #        |\n"
"|  |.....................|     #           #          #         |----+------| |\n"
"|  |.....................|     ########################         |...........| |\n"
"|  |.....................|     #           #                    |...........| |\n"
"|  |.....................|     #    |------+--------------------|...........| |\n"
"|  |.....................|     #    |.......................................| |\n"
"|  |.....................+##########+.......................................| |\n"
"|  |.....................|          |.......................................| |\n"
"|  |---------------------|          |---------------------------------------| |\n"
"|                                                                             |\n"
"|-----------------------------------------------------------------------------|\n"
"|-----------------------------------------------------------------------------|\n"
"|                                                                             |\n"
"| |--------------------------|        |-----------------------|               |\n"
"| |..........................|        |.......................|               |\n"
"| |..........................+########+.......................|-------|       |\n"
"| |..........................|   #    |...............................|--|    |\n"
"| |..........................|   #    |..................................|--| |\n"
"| |----------+---------------|   #    |----+----------------|...............| |\n"
"|            #                 #############                |...............| |\n"
"|            #                 #     |-----+------|         |...............| |\n"
"|            #                 #     |............|         |...............| |\n"
"|            ###################     |............|   ######+...............| |\n"
"|            #                 #     |............|   #     |...............| |\n"
"|            #                 #     |-----+------|   #     |--------+------| |\n"
"|  |---------+-----------|     #           #          #              #        |\n"
"|  |.....................|     #           #          #         |----+------| |\n"
"|  |.....................|     ########################         |...........| |\n"
"|  |.....................|     #           #                    |...........| |\n"
"|  |.....................|     #    |------+--------------------|...........| |\n"
"|  |.....................|     #    |.......................................| |\n"
"|  |.....................+##########+.......................................| |\n"
"|  |.....................|          |.......................................| |\n"
"|  |---------------------|          |---------------------------------------| |\n"
"|                                                                             |\n"
"|-----------------------------------------------------------------------------|\n"
"|-----------------------------------------------------------------------------|\n"
"|                                                                             |\n"
"| |--------------------------|        |-----------------------|               |\n"
"| |..........................|        |.......................|               |\n"
"| |..........................+########+.......................|-------|       |\n"
"| |..........................|   #    |...............................|--|    |\n"
"| |..........................|   #    |..................................|--| |\n"
"| |----------+---------------|   #    |----+----------------|...............| |\n"
"|            #                 #############                |...............| |\n"
"|            #                 #     |-----+------|         |...............| |\n"
"|            #                 #     |............|         |...............| |\n"
"|            ###################     |............|   ######+...............| |\n"
"|            #                 #     |............|   #     |...............| |\n"
"|            #                 #     |-----+------|   #     |--------+------| |\n"
"|  |---------+-----------|     #           #          #              #        |\n"
"|  |.....................|     #           #          #         |----+------| |\n"
"|  |.....................|     ########################         |...........| |\n"
"|  |.....................|     #           #                    |...........| |\n"
"|  |.....................|     #    |------+--------------------|...........| |\n"
"|  |.....................|     #    |.......................................| |\n"
"|  |.....................+##########+.......................................| |\n"
"|  |.....................|          |.......................................| |\n"
"|  |---------------------|          |---------------------------------------| |\n"
"|                                                                             |\n"
"|-----------------------------------------------------------------------------|\n"
"|-----------------------------------------------------------------------------|\n"
"|                                                                             |\n"
"| |--------------------------|        |-----------------------|               |\n"
"| |..........................|        |.......................|               |\n"
"| |..........................+########+.......................|-------|       |\n"
"| |..........................|   #    |...............................|--|    |\n"
"| |..........................|   #    |..................................|--| |\n"
"| |----------+---------------|   #    |----+----------------|...............| |\n"
"|            #                 #############                |...............| |\n"
"|            #                 #     |-----+------|         |...............| |\n"
"|            #                 #     |............|         |...............| |\n"
"|            ###################     |............|   ######+...............| |\n"
"|            #                 #     |............|   #     |...............| |\n"
"|            #                 #     |-----+------|   #     |--------+------| |\n"
"|  |---------+-----------|     #           #          #              #        |\n"
"|  |.....................|     #           #          #         |----+------| |\n"
"|  |.....................|     ########################         |...........| |\n"
"|  |.....................|     #           #                    |...........| |\n"
"|  |.....................|     #    |------+--------------------|...........| |\n"
"|  |.....................|     #    |.......................................| |\n"
"|  |.....................+##########+.......................................| |\n"
"|  |.....................|          |.......................................| |\n"
"|  |---------------------|          |---------------------------------------| |\n"
"|                                                                             |\n"
"|-----------------------------------------------------------------------------|\n");