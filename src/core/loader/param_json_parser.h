// SPDX-FileCopyrightText: Copyright 2025 shadPS5 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <core/common/types.h>

namespace Core::Loader {

	using json = nlohmann::json;

	struct AddCont {
		std::vector<std::string> serviceIdForSharing;
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AddCont, serviceIdForSharing)

		struct Amm {
		int pagetableMemorySizeInMib;
		int vaRangeInGib;
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Amm, pagetableMemorySizeInMib, vaRangeInGib)

		struct GameIntent {
		struct PermittedIntent {
			std::string intentType;
		};
		std::vector<PermittedIntent> permittedIntents;
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GameIntent::PermittedIntent, intentType)
		NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GameIntent, permittedIntents)

		struct Kernel {
		int cpuPageTableSize;
		int flexibleMemorySize;
		int gpuPageTableSize;
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Kernel, cpuPageTableSize, flexibleMemorySize, gpuPageTableSize)

		struct LocalizedParameters {
		struct LanguageEntry {
			std::string titleName;
		};
		std::unordered_map<std::string, LanguageEntry> languages;
		std::string defaultLanguage;
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LocalizedParameters::LanguageEntry, titleName)

		inline void to_json(json& j, const LocalizedParameters& lp) {
		j = lp.languages;
		j["defaultLanguage"] = lp.defaultLanguage;
	}
	inline void from_json(const json& j, LocalizedParameters& lp) {
		lp.defaultLanguage = j.at("defaultLanguage");
		for (auto& [key, val] : j.items()) {
			if (key != "defaultLanguage") {
				lp.languages[key] = val.get<LocalizedParameters::LanguageEntry>();
			}
		}
	}

	struct PubTools {
		std::string creationDate;
		std::string loudnessSnd0;
		bool submission;
		std::string toolVersion;
	};
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PubTools, creationDate, loudnessSnd0, submission, toolVersion)

		struct AgeLevel {
		std::unordered_map<std::string, int> countryRatings;
		int defaultRating;
	};

	inline void to_json(json& j, const AgeLevel& a) {
		j = a.countryRatings;
		j["default"] = a.defaultRating;
	}
	inline void from_json(const json& j, AgeLevel& a) {
		a.defaultRating = j.at("default");
		a.countryRatings = j.get<std::unordered_map<std::string, int>>();
		a.countryRatings.erase("default");
	}

	struct ParamJson {
		AddCont addcont;
		AgeLevel ageLevel;
		std::optional<Amm> amm;
		u32 applicationCategoryType;
		std::string applicationDrmType;
		u32 attribute;
		u32 attribute2;
		u32 attribute3;
		std::optional<std::string> backgroundBasematType;
		std::string conceptId;
		u32 contentBadgeType;
		std::string contentId;
		std::string contentVersion;
		std::optional<std::string> deeplinkUri;
		std::optional <u64> downloadDataSize;
		GameIntent gameIntent;
		std::optional <Kernel> kernel;
		LocalizedParameters localizedParameters;
		std::string masterVersion;
		std::optional <std::string> originContentVersion;
		PubTools pubtools;
		std::string requiredSystemSoftwareVersion;
		std::string sdkVersion;
		std::optional <std::string> targetContentVersion;
		std::string titleId;
		u32 userDefinedParam1;
		u32 userDefinedParam2;
		u32 userDefinedParam3;
		u32 userDefinedParam4;
		std::string versionFileUri;
	};

	void to_json(nlohmann::json& j, const ParamJson& p) {
		j = nlohmann::json{
			{"addcont", p.addcont},
			{"ageLevel", p.ageLevel},
			{"applicationCategoryType", p.applicationCategoryType},
			{"applicationDrmType", p.applicationDrmType},
			{"attribute", p.attribute},
			{"attribute2", p.attribute2},
			{"attribute3", p.attribute3},
			{"conceptId", p.conceptId},
			{"contentBadgeType", p.contentBadgeType},
			{"contentId", p.contentId},
			{"contentVersion", p.contentVersion},
			{"gameIntent", p.gameIntent},
			{"localizedParameters", p.localizedParameters},
			{"masterVersion", p.masterVersion},
			{"pubtools", p.pubtools},
			{"requiredSystemSoftwareVersion", p.requiredSystemSoftwareVersion},
			{"sdkVersion", p.sdkVersion},
			{"titleId", p.titleId},
			{"userDefinedParam1", p.userDefinedParam1},
			{"userDefinedParam2", p.userDefinedParam2},
			{"userDefinedParam3", p.userDefinedParam3},
			{"userDefinedParam4", p.userDefinedParam4},
			{"versionFileUri", p.versionFileUri}
		};

		if (p.amm.has_value()) {
			j["amm"] = p.amm.value();
		}
		if (p.kernel.has_value()) {
			j["kernel"] = p.kernel.value();
		}
		if (p.originContentVersion.has_value()) {
			j["originContentVersion"] = p.originContentVersion.value();
		}
		if (p.targetContentVersion.has_value()) {
			j["targetContentVersion"] = p.targetContentVersion.value();
		}
		if (p.backgroundBasematType.has_value()) {
			j["backgroundBasematType"] = p.backgroundBasematType.value();
		}
		if (p.deeplinkUri.has_value()) {
			j["deeplinkUri"] = p.deeplinkUri.value();
		}
		if (p.downloadDataSize.has_value()) {
			j["downloadDataSize"] = p.downloadDataSize.value();
		}
	}

	void from_json(const nlohmann::json& j, ParamJson& p) {
		j.at("addcont").get_to(p.addcont);
		j.at("ageLevel").get_to(p.ageLevel);
		if (j.contains("amm") && !j["amm"].is_null()) {
			p.amm = j.at("amm").get<Amm>();
		}
		else {
			p.amm = std::nullopt;
		}
		if (j.contains("kernel") && !j["kernel"].is_null()) {
			p.kernel = j.at("kernel").get<Kernel>();
		}
		else {
			p.kernel = std::nullopt;
		}
		if (j.contains("originContentVersion") && !j["originContentVersion"].is_null()) {
			p.originContentVersion = j.at("originContentVersion").get<std::string>();
		}
		else {
			p.originContentVersion = std::nullopt;
		}
		if (j.contains("targetContentVersion") && !j["targetContentVersion"].is_null()) {
			p.targetContentVersion = j.at("targetContentVersion").get<std::string>();
		}
		else {
			p.targetContentVersion = std::nullopt;
		}
		if (j.contains("backgroundBasematType") && !j["backgroundBasematType"].is_null()) {
			p.backgroundBasematType = j.at("backgroundBasematType").get<std::string>();
		}
		else {
			p.backgroundBasematType = std::nullopt;
		}
		if (j.contains("deeplinkUri") && !j["deeplinkUri"].is_null()) {
			p.deeplinkUri = j.at("deeplinkUri").get<std::string>();
		}
		else {
			p.deeplinkUri = std::nullopt;
		}
		if (j.contains("downloadDataSize") && !j["downloadDataSize"].is_null()) {
			p.downloadDataSize = j.at("downloadDataSize").get<u64>();
		}
		else {
			p.downloadDataSize = std::nullopt;
		}

		j.at("applicationCategoryType").get_to(p.applicationCategoryType);
		j.at("applicationDrmType").get_to(p.applicationDrmType);
		j.at("attribute").get_to(p.attribute);
		j.at("attribute2").get_to(p.attribute2);
		j.at("attribute3").get_to(p.attribute3);
		j.at("conceptId").get_to(p.conceptId);
		j.at("contentBadgeType").get_to(p.contentBadgeType);
		j.at("contentId").get_to(p.contentId);
		j.at("contentVersion").get_to(p.contentVersion);
		j.at("gameIntent").get_to(p.gameIntent);
		j.at("localizedParameters").get_to(p.localizedParameters);
		j.at("masterVersion").get_to(p.masterVersion);
		j.at("pubtools").get_to(p.pubtools);
		j.at("requiredSystemSoftwareVersion").get_to(p.requiredSystemSoftwareVersion);
		j.at("sdkVersion").get_to(p.sdkVersion);
		j.at("titleId").get_to(p.titleId);
		j.at("userDefinedParam1").get_to(p.userDefinedParam1);
		j.at("userDefinedParam2").get_to(p.userDefinedParam2);
		j.at("userDefinedParam3").get_to(p.userDefinedParam3);
		j.at("userDefinedParam4").get_to(p.userDefinedParam4);
		j.at("versionFileUri").get_to(p.versionFileUri);
	}

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ParamJson,
		addcont,
		ageLevel,
		amm,
		applicationCategoryType,
		applicationDrmType,
		attribute,
		attribute2,
		attribute3,
		conceptId,
		contentBadgeType,
		contentId,
		contentVersion,
		downloadDataSize,
		gameIntent,
		kernel,
		localizedParameters,
		masterVersion,
		originContentVersion,
		pubtools,
		requiredSystemSoftwareVersion,
		sdkVersion,
		targetContentVersion,
		titleId,
		userDefinedParam1,
		userDefinedParam2,
		userDefinedParam3,
		userDefinedParam4,
		versionFileUri
	)
}