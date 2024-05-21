#pragma once
#include <string>
#include <map>
enum Filetype {
	INVALID,
	SNIRF,
	CSV,
	EEG_FILE,
	EXPERIMENT, 
	PIPELINE,
};

inline static std::map<Filetype, std::string> type_to_suffix_map = {
	{	SNIRF		,	".snirf"	},
	{	CSV			,	".csv"		},
	{	EEG_FILE	,	".EEG"		},
	{	EXPERIMENT	,	".expr"		},
	{	PIPELINE	,	".pipe"		},
};

inline static std::map<std::string, Filetype> suffix_to_type_map = {
	{	".snirf"	,	SNIRF		},
	{	".csv"		,	CSV			},
	{	".EEG"		,	EEG_FILE	},
	{	".expr"		,	EXPERIMENT	},
	{	".pipe"		,	PIPELINE	},
};

inline const std::string FiletypeToSuffix(Filetype filetype) {
	if (type_to_suffix_map.find(filetype) != type_to_suffix_map.end()) {
		return type_to_suffix_map[filetype];
	}
	return "INVALID";
}
inline const Filetype SuffixToFiletype(std::string suffix) {
	if (suffix_to_type_map.find(suffix) != suffix_to_type_map.end()) {
		return suffix_to_type_map[suffix];
	}
	return INVALID;
}

inline const std::string GetSuffix(const std::string& filename) {
	int idx = filename.find_last_of('.');
	std::string suffix = filename.substr(idx, filename.size() - idx);
	return suffix;
}

inline const Filetype ParseFiletype(const std::string& filename) {
	int idx = filename.find_last_of('.');
	std::string suffix = filename.substr(idx, filename.size() - idx);
	if (suffix == ".snirf") {
		return SNIRF;
	}
	if (suffix == ".expr") {
		return EXPERIMENT;
	}
	if (suffix == ".pipe") {
		return PIPELINE;
	}
	return INVALID;
}

inline const std::string FiletypeToString(Filetype filetype)
{
    switch (filetype)
    {
    case INVALID:		return "INVALID";
    case SNIRF:			return "SNIRF";
    case CSV:			return "Windows";
    case EEG_FILE:		return "EEG";
	case EXPERIMENT:	return "EXPERIMENT";
	case PIPELINE:		return "PIPELINE";
    default:        return "UNKNOWN FILETYPE ENUM";
    }
}