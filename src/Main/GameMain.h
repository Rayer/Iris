/**
 * Project Iris
 */


#ifndef _GAMEMAIN_H
#define _GAMEMAIN_H





namespace Iris {
    class Context;
    class MoMLayer;
    class GameMain {

    private:
        MoMLayer *mom_layer;

    public:
        /**
         * @param context
         */
        void loop(Context *context);
    };

}

#endif //_GAMEMAIN_H