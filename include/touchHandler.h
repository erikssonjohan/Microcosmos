//
// Created by Ingela Rossing on 27/03/17.
//

#ifndef MIKROKOSMOS_TOUCHHANDLER_H
#define MIKROKOSMOS_TOUCHHANDLER_H
#include <vector>
#include <algorithm>
#include <iostream>
#include "SDL.h"
#include "RealCard.h"
#include "VirtualCard.h"


class touchHandler {
public:

    /*!
     *
     * Handle a FINGERDOWN event
     *
     * @param tfe -
     */
    void addFinger(SDL_TouchFingerEvent & tfe,std::vector<VirtualCard> &vc,  std::vector<RealCard>  &rc); //FINGERDOWN


    /*!
     *
     * Handle a FINGERMOTION event
     *
     * @param tfe -
     */
    void updateFinger(SDL_TouchFingerEvent &tfe, std::vector<RealCard>  &rc); //FINGERMOTION

    /*!
     *
     * Handle a FINGERUP event
     * Function to remove tfe from the vector using fingerId
     * @param fid -
     */
    void removeFinger(SDL_FingerID fid, std::vector<RealCard>  &rc); //FINGERUP

    /*!
     *
     * @param i
     * @return
     */
    SDL_TouchFingerEvent getTfe(int i){return vec[i];}

private:
    std::vector<SDL_TouchFingerEvent> vec;

};


#endif //MIKROKOSMOS_TOUCHHANDLER_H
