// n2p2 - A neural network potential package
// Copyright (C) 2018 Andreas Singraber (University of Vienna)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "Settings.h"
#include "utility.h"
#include <fstream>   // std::ifstream
#include <stdexcept> // std::runtime_error
#include <tuple>     // std::tie

using namespace std;
using namespace nnp;
using namespace settings;

map<string, shared_ptr<settings::Key>> const createKnownKeywordsMap()
{
    // Main keyword names and descriptions.
    map<string, string> m;
    // Alternative names.
    map<string, vector<string>> a;
    // Complete keyword map to return.
    map<string, shared_ptr<settings::Key>> r;

    // Required for prediction.
    m["number_of_elements"                 ] = "";
    m["elements"                           ] = "";
    m["atom_energy"                        ] = "";
    m["cutoff_type"                        ] = "";
    m["symfunction_short"                  ] = "";
    m["scale_symmetry_functions"           ] = "";
    m["scale_min_short"                    ] = "";
    m["scale_max_short"                    ] = "";
    m["center_symmetry_functions"          ] = "";
    m["scale_symmetry_functions_sigma"     ] = "";
    m["global_hidden_layers_short"         ] = "";
    m["global_hidden_layers_electrostatic" ] = "";
    m["global_nodes_short"                 ] = "";
    m["global_nodes_electrostatic"         ] = "";
    m["global_activation_short"            ] = "";
    m["global_activation_electrostatic"    ] = "";
    m["element_hidden_layers_short"        ] = "";
    m["element_hidden_layers_electrostatic"] = "";
    m["element_nodes_short"                ] = "";
    m["element_nodes_electrostatic"        ] = "";
    m["element_activation_short"           ] = "";
    m["element_activation_electrostatic"   ] = "";
    m["normalize_nodes"                    ] = "";
    m["mean_energy"                        ] = "";
    m["conv_length"                        ] = "";
    m["conv_energy"                        ] = "";
    m["conv_charge"                        ] = "";
    m["nnp_type"                           ] = "";
    m["fixed_gausswidth"                   ] = "";
    m["ewald_truncation_error_method"      ] = "";
    m["kspace_solver"                      ] = "";
    m["ewald_prec"                         ] = "";
    m["screen_electrostatics"              ] = "";
    m["four_pi_epsilon"                    ] = "";

    // Training keywords.
    m["random_seed"                        ] = "";
    m["test_fraction"                      ] = "";
    m["epochs"                             ] = "";
    m["normalize_data_set"                 ] = "";
    m["use_short_forces"                   ] = "";
    m["rmse_threshold"                     ] = "";
    m["rmse_threshold_energy"              ] = "";
    m["rmse_threshold_force"               ] = "";
    m["rmse_threshold_charge"              ] = "";
    m["rmse_threshold_trials"              ] = "";
    m["rmse_threshold_trials_energy"       ] = "";
    m["rmse_threshold_trials_force"        ] = "";
    m["rmse_threshold_trials_charge"       ] = "";
    m["energy_fraction"                    ] = "";
    m["force_fraction"                     ] = "";
    m["force_energy_ratio"                 ] = "";
    m["charge_fraction"                    ] = "";
    m["use_old_weights_short"              ] = "";
    m["use_old_weights_charge"             ] = "";
    m["weights_min"                        ] = "";
    m["weights_max"                        ] = "";
    m["initial_hardness"                   ] = "";
    m["nguyen_widrow_weights_short"        ] = "";
    m["nguyen_widrow_weights_charge"       ] = "";
    m["precondition_weights"               ] = "";
    m["main_error_metric"                  ] = "";
    m["write_trainpoints"                  ] = "";
    m["write_trainforces"                  ] = "";
    m["write_traincharges"                 ] = "";
    m["write_weights_epoch"                ] = "";
    m["write_neuronstats"                  ] = "";
    m["write_trainlog"                     ] = "";
    m["repeated_energy_update"             ] = "";
    m["updater_type"                       ] = "";
    m["parallel_mode"                      ] = "";
    m["jacobian_mode"                      ] = "";
    m["update_strategy"                    ] = "";
    m["selection_mode"                     ] = "";
    m["selection_mode_energy"              ] = "";
    m["selection_mode_force"               ] = "";
    m["selection_mode_charge"              ] = "";
    m["task_batch_size_energy"             ] = "";
    m["task_batch_size_force"              ] = "";
    m["task_batch_size_charge"             ] = "";
    m["gradient_type"                      ] = "";
    m["gradient_eta"                       ] = "";
    m["gradient_adam_eta"                  ] = "";
    m["gradient_adam_beta1"                ] = "";
    m["gradient_adam_beta2"                ] = "";
    m["gradient_adam_epsilon"              ] = "";
    m["kalman_type"                        ] = "";
    m["kalman_epsilon"                     ] = "";
    m["kalman_eta"                         ] = "";
    m["kalman_etatau"                      ] = "";
    m["kalman_etamax"                      ] = "";
    m["kalman_q0"                          ] = "";
    m["kalman_qtau"                        ] = "";
    m["kalman_qmin"                        ] = "";
    m["kalman_lambda_short"                ] = "";
    m["kalman_nue_short"                   ] = "";
    m["memorize_symfunc_results"           ] = "";
    m["force_weight"                       ] = "";

    // Alternative keyword names.
    a["nnp_type"             ] = {"nnp_generation", "nnp_type_gen", "nnp_gen"};
    a["rmse_threshold_energy"] = {"short_energy_error_threshold"};
    a["rmse_threshold_force" ] = {"short_force_error_threshold"};
    a["energy_fraction"      ] = {"short_energy_fraction"};
    a["force_fraction"       ] = {"short_force_fraction"};
    a["symfunction_short"    ] = {"symfunction"};

    for (auto im : m)
    {
        // Check if keyword was already inserted.
        if (r.find(im.first) != r.end())
        {
            throw runtime_error("ERROR: Multiple definition of keyword.\n");
        }
        // Insert new shared pointer to a Key object.
        r[im.first] = make_shared<settings::Key>();
        // Add main keyword as first entry in alternatives list.
        r.at(im.first)->addAlternative(im.first);
        // Add description text.
        r.at(im.first)->setDescription(im.second);
        // Check if alternative keywords exist.
        if (a.find(im.first) != a.end())
        {
            // Loop over all alternative keywords.
            for (auto alt : a.at(im.first))
            {
                // Check if alternative keyword is already inserted.
                if (r.find(alt) != r.end())
                {
                    throw runtime_error("ERROR: Multiple definition of "
                                        "alternative keyword.\n");
                }
                // Set map entry, i.e. shared pointer, to Key object.
                r[alt] = r.at(im.first);
                // Add alternative keyword to list.
                r[alt]->addAlternative(alt);
            }
        }
    }

    return r;
}

Settings::KeywordList Settings::knownKeywords = createKnownKeywordsMap();

string Settings::operator[](string const& keyword) const
{
    return getValue(keyword);
}


size_t Settings::loadFile(string const& fileName)
{
    this->fileName = fileName;

    readFile();
    return parseLines();
}
bool Settings::keywordExists(Key const& key,
                             bool const exact) const
{
    return keywordExists(key.getMainKeyword(), exact);
}
bool Settings::keywordExists(string const& keyword, bool exact) const
{
    if (knownKeywords.find(keyword) == knownKeywords.end())
    {
        throw runtime_error("ERROR: Not in the list of allowed keyword: \"" +
                            keyword + "\".\n");
    }
    if (exact || knownKeywords.at(keyword)->hasUniqueKeyword())
    {
        return (contents.find(keyword) != contents.end());
    }
    else
    {
        for (auto alternative : *knownKeywords.at(keyword))
        {
            if (contents.find(alternative) != contents.end()) return true;
        }
    }

    return false;
}

string Settings::keywordCheck(string const& keyword) const
{
    bool exists = keywordExists(keyword, false);
    bool unique = knownKeywords.at(keyword)->hasUniqueKeyword();
    if (!exists)
    {
        if (unique)
        {
            throw std::runtime_error("ERROR: Keyword \"" + keyword
                                     + "\" not found.\n");
        }
        else
        {
            throw std::runtime_error("ERROR: Neither keyword \"" + keyword
                                     + "\" nor alternative keywords found.\n");
        }
    }

    bool exact = keywordExists(keyword, true);
    if (!exact)
    {
        for (auto const& alt : *knownKeywords.at(keyword))
        {
            if (contents.find(alt) != contents.end()) return alt;
        }
    }

    return keyword;
}

string Settings::getValue(Key const& key) const
{
    return contents.find(key.getMainKeyword())->second.first;
}

string Settings::getValue(string const& keyword) const
{
    return contents.find(keywordCheck(keyword))->second.first;
}

Settings::KeyRange Settings::getValues(string const& keyword) const
{
    return contents.equal_range(keywordCheck(keyword));
}

vector<string> Settings::info() const
{
    return log;
}

vector<string> Settings::getSettingsLines() const
{
    return lines;
}

void Settings::readFile()
{
    ifstream file;
    string   line;

    log.push_back(strpr("Settings file name: %s\n", fileName.c_str()));
    file.open(fileName.c_str());
    if (!file.is_open())
    {
        throw runtime_error("ERROR: Could not open file: \"" + fileName
                            + "\".\n");
    }

    while (getline(file, line))
    {
        lines.push_back(line);
    }

    file.close();

    log.push_back(strpr("Read %zu lines.\n", lines.size()));

    return;
}

void Settings::writeSettingsFile(ofstream* const&           file,
                                 map<size_t, string> const& replacements) const
{
    if (!file->is_open())
    {
        runtime_error("ERROR: Could not write to file.\n");
    }

    size_t i = 0;
    for (auto const& l : lines)
    {
        if (replacements.find(i) != replacements.end())
        {
            (*file) << replacements.at(i);
        }
        else (*file) << l << '\n';
        i++;
    }

    return;
}

size_t Settings::parseLines()
{
    for (size_t i = 0; i < lines.size(); ++i)
    {
        string line = lines.at(i);

        // ignore empty and comment lines
        if (line.empty())
        {
            continue;
        }
        // check for empty lines in Windows format
        if (line == "\r")
        {
            continue;
        }
        if (line.find('#') != string::npos)
        {
            line.erase(line.find('#'));
        }
        if (line.find('!') != string::npos)
        {
            line.erase(line.find('!'));
        }
        if (line.find_first_not_of(' ') == string::npos)
        {
            continue;
        }

        // remove leading and trailing whitespaces and trim separating spaces
        line = reduce(line);

        // find separator position
        size_t const separatorPosition = line.find_first_of(" ");
        string key;
        pair<string, size_t> value;

        if (separatorPosition == string::npos)
        {
            // first check for single keyword without value
            key = line;
            value = pair<string, size_t>("", i);
        }
        else
        {
            // one or more arguments
            key = line.substr(0, separatorPosition);
            value = pair<string, size_t>(line.erase(0, separatorPosition + 1),
                                         i);
        }

        contents.insert(pair<string, pair<string, size_t> >(key, value));
    }

    size_t numProblems = 0;
    size_t numCritical = 0;
    tie(numProblems, numCritical) = sanityCheck();
    if (numProblems > 0)
    {
        log.push_back(strpr("WARNING: %zu problems detected (%zu critical).\n",
                            numProblems, numCritical));
    }

    log.push_back(strpr("Found %zu lines with keywords.\n", contents.size()));

    return numCritical;
}

pair<size_t, size_t> Settings::sanityCheck()
{
    size_t countProblems = 0;
    size_t countCritical = 0;

    // check for unknown keywords
    for (multimap<string, pair<string, size_t> >::const_iterator
         it = contents.begin(); it != contents.end(); ++it)
    {
        if (knownKeywords.find((*it).first) == knownKeywords.end())
        {
            countProblems++;
            log.push_back(strpr(
                "WARNING: Unknown keyword \"%s\" at line %zu.\n",
                (*it).first.c_str(),
                (*it).second.second + 1));
        }
    }

    // check for multiple instances of known keywords (with exceptions)
    for (KeywordList::const_iterator it = knownKeywords.begin();
         it != knownKeywords.end(); ++it)
    {
        if (contents.count((*it).first) > 1
            && (*it).first != "symfunction"
            && (*it).first != "symfunction_short"
            && (*it).first != "atom_energy"
            && (*it).first != "element_nodes_short"
            && (*it).first != "fixed_gausswidth"
            && (*it).first != "initial_hardness")
        {
            countProblems++;
            countCritical++;
            log.push_back(strpr(
                "WARNING (CRITICAL): Multiple instances of \"%s\" detected.\n",
                (*it).first.c_str()));
        }
    }

    // Check for usage of multiple keyword versions.
    for (KeywordList::const_iterator it = knownKeywords.begin();
         it != knownKeywords.end(); ++it)
    {
        if (it->second->hasUniqueKeyword()) continue;
        vector<string> duplicates;
        for (auto keyword : *it->second)
        {
            if (contents.find(keyword) != contents.end())
            {
                duplicates.push_back(keyword);
            }
        }
        if (duplicates.size() > 1)
        {
            countProblems++;
            countCritical++;
            log.push_back(strpr(
                "WARNING (CRITICAL): Multiple alternative versions of keyword "
                "\"%s\" detected:.\n", (*it).first.c_str()));
            for (auto d : duplicates)
            {
                log.push_back(strpr(
                    "                    - \"%s\"\n", d.c_str()));
            }
        }
    }

    return make_pair(countProblems, countCritical);
}
