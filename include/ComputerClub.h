#include <iostream>
#include <view/Reader.h>
#include <view/Writer.h>
#include <model/service/ComputerClubService.h>
#include <model/ComputerClub.h>
#include <model/Event.h>
#include <controller/ComputerClubController.h>
#include <repository/ClientRamRepository.h>
#include <repository/TableRamRepository.h>

void ComputerClubRun(std::istream& is, std::ostream& os);