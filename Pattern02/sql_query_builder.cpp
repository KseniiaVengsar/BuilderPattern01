#include "sql_query_builder.h"

SqlSelectQueryBuilder::SqlSelectQueryBuilder() {}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& column) {
    columns_.push_back(column);
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumns(const std::vector<std::string>& columns) noexcept {
    columns_ = columns;
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& table) {
    from_ = table;
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& column, const std::string& value) {
    where_.push_back(std::make_pair(column, value));
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& kv) noexcept {
    for (const auto& pair : kv) {
        where_.push_back(pair);
    }
    return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery() const {
    std::string query = "SELECT ";

    if (!hasColumns()) {
        query += "* ";
    }
    else {
        for (const auto& column : columns_) {
            query += column + ", ";
        }
        query.pop_back(); 
        query.pop_back(); 
    }

    query += " FROM " + from_;

    if (!where_.empty()) {
        query += " WHERE ";
        for (const auto& condition : where_) {
            query += condition.first + "=" + condition.second + " AND ";
        }
        query.pop_back(); 
        query.pop_back(); 
    }

    query += ";";

    return query;
}

bool SqlSelectQueryBuilder::hasColumns() const {
    return !columns_.empty();
}