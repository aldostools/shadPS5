#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "src/core/loader/param_json_parser.h"

using namespace Core::Loader;

void printAddCont(const AddCont& addcont) {
	std::cout << "AddCont:\n";
	std::cout << "  serviceIdForSharing:\n";
	for (const auto& id : addcont.serviceIdForSharing) {
		std::cout << "    - \"" << id << "\"\n";
	}
}

void printAmm(const std::optional<Amm>& ammOpt) {
	if (ammOpt) {
		printAmm(*ammOpt);
	}
}
void printAmm(const Amm& amm) {
	std::cout << "Amm:\n";
	std::cout << "  pagetableMemorySizeInMib: " << amm.pagetableMemorySizeInMib << "\n";
	std::cout << "  vaRangeInGib: " << amm.vaRangeInGib << "\n";
}


void printGameIntent(const GameIntent& gameIntent) {
	std::cout << "GameIntent:\n";
	std::cout << "  permittedIntents:\n";
	for (const auto& intent : gameIntent.permittedIntents) {
		std::cout << "    - intentType: \"" << intent.intentType << "\"\n";
	}
}

void printKernel(const std::optional<Kernel>& kernelOpt) {
	if (kernelOpt) {
		printKernel(*kernelOpt);
	}
}

void printKernel(const Kernel& kernel) {
	std::cout << "Kernel:\n";
	std::cout << "  cpuPageTableSize: " << kernel.cpuPageTableSize << "\n";
	std::cout << "  flexibleMemorySize: " << kernel.flexibleMemorySize << "\n";
	std::cout << "  gpuPageTableSize: " << kernel.gpuPageTableSize << "\n";
}

void printLocalizedParameters(const LocalizedParameters& localizedParameters) {
	std::cout << "LocalizedParameters:\n";
	std::cout << "  defaultLanguage: \"" << localizedParameters.defaultLanguage << "\"\n";
	std::cout << "  languages:\n";
	for (const auto& [lang, entry] : localizedParameters.languages) {
		std::cout << "    " << std::left << std::setw(10) << lang
			<< ": \"" << entry.titleName << "\"\n";
	}
}

void printPubTools(const PubTools& pubtools) {
	std::cout << "PubTools:\n";
	std::cout << "  creationDate: \"" << pubtools.creationDate << "\"\n";
	std::cout << "  loudnessSnd0: \"" << pubtools.loudnessSnd0 << "\"\n";
	std::cout << "  submission: " << std::boolalpha << pubtools.submission << "\n";
	std::cout << "  toolVersion: \"" << pubtools.toolVersion << "\"\n";
}

void printAgeLevel(const AgeLevel& ageLevel) {
	std::cout << "AgeLevel:\n";
	std::cout << "  default: " << ageLevel.defaultRating << "\n";
	std::cout << "  countryRatings:\n";
	for (const auto& [country, rating] : ageLevel.countryRatings) {
		std::cout << "    " << std::left << std::setw(4) << country
			<< ": " << rating << "\n";
	}
}

void printParamJson(const ParamJson& params) {
	std::cout << "========================================\n";
	std::cout << "          PARAM.JSON CONTENTS           \n";
	std::cout << "========================================\n\n";

	// Basic info
	std::cout << "Basic Information:\n";
	std::cout << "  contentId: \"" << params.contentId << "\"\n";
	std::cout << "  titleId: \"" << params.titleId << "\"\n";
	std::cout << "  conceptId: \"" << params.conceptId << "\"\n";
	std::cout << "  contentVersion: \"" << params.contentVersion << "\"\n";
	std::cout << "  masterVersion: \"" << params.masterVersion << "\"\n";
	if (params.originContentVersion.has_value()) {
		std::cout << "  originContentVersion: \"" << params.originContentVersion.value() << "\"\n";
	}
	if (params.targetContentVersion.has_value()) {
		std::cout << "  targetContentVersion: \"" << params.targetContentVersion.value() << "\"\n";
	}
	std::cout << "  requiredSystemSoftwareVersion: \"" << params.requiredSystemSoftwareVersion << "\"\n";
	std::cout << "  sdkVersion: \"" << params.sdkVersion << "\"\n";
	std::cout << "  versionFileUri: \"" << params.versionFileUri << "\"\n\n";

	// Application info
	std::cout << "Application Info:\n";
	std::cout << "  applicationCategoryType: " << params.applicationCategoryType << "\n";
	std::cout << "  applicationDrmType: \"" << params.applicationDrmType << "\"\n";
	std::cout << "  contentBadgeType: " << params.contentBadgeType << "\n";
	if (params.downloadDataSize.has_value()) {
		std::cout << "  downloadDataSize: " << params.downloadDataSize.value() << "\n";
	}

	// Attributes
	std::cout << "Attributes:\n";
	std::cout << "  attribute: " << params.attribute << "\n";
	std::cout << "  attribute2: " << params.attribute2 << "\n";
	std::cout << "  attribute3: " << params.attribute3 << "\n\n";

	// User defined params
	std::cout << "User Defined Parameters:\n";
	std::cout << "  userDefinedParam1: " << params.userDefinedParam1 << "\n";
	std::cout << "  userDefinedParam2: " << params.userDefinedParam2 << "\n";
	std::cout << "  userDefinedParam3: " << params.userDefinedParam3 << "\n";
	std::cout << "  userDefinedParam4: " << params.userDefinedParam4 << "\n\n";

	// Print nested structures
	printAddCont(params.addcont);
	std::cout << "\n";
	printAgeLevel(params.ageLevel);
	std::cout << "\n";
	printAmm(params.amm);
	std::cout << "\n";
	printGameIntent(params.gameIntent);
	std::cout << "\n";
	//printKernel(params.kernel);
	//std::cout << "\n";
	printLocalizedParameters(params.localizedParameters);
	std::cout << "\n";
	printPubTools(params.pubtools);
}

int main() {
	try {
		// Read JSON file
		std::ifstream file("param.json");
		if (!file.is_open()) {
			throw std::runtime_error("Failed to open param.json");
		}

		// Parse JSON
		json j = json::parse(file);
		ParamJson params = j.get<ParamJson>();

		// Print all contents
		printParamJson(params);

	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}