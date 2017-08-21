/*
 * condition.hpp
 *
 *  Created on: Aug 20, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include "common.h"

namespace hacks { namespace shared { namespace walkbot {

class ConditionPart {
public:
	ConditionPart(ComplexCondition&, const nlohmann::json& json);
	operator nlohmann::json() const;

	bool pass() const;
public:
	nlohmann::json json_;
	ComplexCondition& parent_;
};

class ComplexCondition {
public:
	typedef Handle<ComplexCondition, uuid_t> handle_t;
public:
	ComplexCondition(Pathing& parent);
	ComplexCondition(Pathing& parent, const uuid_t& uuid, const nlohmann::json& json);
	operator nlohmann::json() const;

	bool pass() const;
public:
	std::vector<ConditionPart> conditions_ {};
	Pathing& parent_;
};

}}}

