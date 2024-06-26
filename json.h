/*
 * Copyright (c) 2013-2024 dresden elektronik ingenieurtechnik gmbh.
 * All rights reserved.
 *
 * The software in this package is published under the terms of the BSD
 * style license a copy of which has been included with this distribution in
 * the LICENSE.txt file.
 *
 */

#ifndef JSON_H
#define JSON_H

#include <QVariant>
#include <QString>

/* CJ
 * Low level JSON module
 */
#include "cj/cj.h"

/*
 * CJ extra modules, have no header thus declare protoypes here.
 */
#ifdef __cplusplus
extern "C" {
#endif

int cj_copy_ref_utf8(cj_ctx *ctx, char *buf, unsigned size, cj_token_ref ref);
int cj_ref_to_boolean(cj_ctx *ctx, int *result, cj_token_ref ref);
int cj_ref_to_double(cj_ctx *ctx, double *result, cj_token_ref ref);
int cj_ref_to_long(cj_ctx *ctx, long *result, cj_token_ref ref);
int cj_ref_to_null(cj_ctx *ctx, cj_token_ref ref);

#ifdef __cplusplus
}
#endif


/**
 * \enum JsonToken
 */
enum JsonToken
{
	JsonTokenNone = 0,
	JsonTokenCurlyOpen = 1,
	JsonTokenCurlyClose = 2,
	JsonTokenSquaredOpen = 3,
	JsonTokenSquaredClose = 4,
	JsonTokenColon = 5,
	JsonTokenComma = 6,
	JsonTokenString = 7,
	JsonTokenNumber = 8,
	JsonTokenTrue = 9,
	JsonTokenFalse = 10,
	JsonTokenNull = 11
};

/**
 * \class Json
 * \brief A JSON data parser
 *
 * Json parses a JSON data into a QVariant hierarchy.
 */
class Json
{
	public:
		/**
		 * Parse a JSON string
		 *
		 * \param json The JSON data
		 */
		static QVariant parse(const QString &json);

		/**
		 * Parse a JSON string
		 *
		 * \param json The JSON data
		 * \param success The success of the parsing
		 */
		static QVariant parse(const QString &json, bool &success);

		/**
		* This method generates a textual JSON representation
		*
		* \param data The JSON data generated by the parser.
		* \param success The success of the serialization
		*/
		static QByteArray serialize(const QVariant &data);

		/**
		* This method generates a textual JSON representation
		*
		* \param data The JSON data generated by the parser.
		* \param success The success of the serialization
		*
		* \return QByteArray Textual JSON representation
		*/
		static QByteArray serialize(const QVariant &data, bool &success);

	private:
		/**
		 * Parses a value starting from index
		 *
		 * \param json The JSON data
		 * \param index The start index
		 * \param success The success of the parse process
		 *
		 * \return QVariant The parsed value
		 */
		static QVariant parseValue(const QString &json, int &index,
								   bool &success);

		/**
		 * Parses an object starting from index
		 *
		 * \param json The JSON data
		 * \param index The start index
		 * \param success The success of the object parse
		 *
		 * \return QVariant The parsed object map
		 */
		static QVariant parseObject(const QString &json, int &index,
									   bool &success);

		/**
		 * Parses an array starting from index
		 *
		 * \param json The JSON data
		 * \param index The starting index
		 * \param success The success of the array parse
		 *
		 * \return QVariant The parsed variant array
		 */
		static QVariant parseArray(const QString &json, int &index,
									   bool &success);

		/**
		 * Parses a string starting from index
		 *
		 * \param json The JSON data
		 * \param index The starting index
		 * \param success The success of the string parse
		 *
		 * \return QVariant The parsed string
		 */
		static QVariant parseString(const QString &json, int &index,
									bool &success);

		/**
		 * Parses a number starting from index
		 *
		 * \param json The JSON data
		 * \param index The starting index
		 *
		 * \return QVariant The parsed number
		 */
		static QVariant parseNumber(const QString &json, int &index);

		/**
		 * Get the last index of a number starting from index
		 *
		 * \param json The JSON data
		 * \param index The starting index
		 *
		 * \return The last index of the number
		 */
		static int lastIndexOfNumber(const QString &json, int index);

		/**
		 * Skip unwanted whitespace symbols starting from index
		 *
		 * \param json The JSON data
		 * \param index The start index
		 */
		static void eatWhitespace(const QString &json, int &index);

		/**
		 * Check what token lies ahead
		 *
		 * \param json The JSON data
		 * \param index The starting index
		 *
		 * \return int The upcoming token
		 */
		static int lookAhead(const QString &json, int index);

		/**
		 * Get the next JSON token
		 *
		 * \param json The JSON data
		 * \param index The starting index
		 *
		 * \return int The next JSON token
		 */
		static int nextToken(const QString &json, int &index);
};


/*!
 * \class JsonBuilder
 * \brief JSON builder class that uses scratch allocator under the hood.
 */
class JsonBuilderPrivate;

class JsonBuilder
{
public:
    JsonBuilder() = delete;
    explicit JsonBuilder(unsigned bufsize);

    void startArray();
    void endArray();
    void startObject();
    void endObject();
    void addKey(const char *key);
    void addNumber(double num);
    void addString(const char *str);

private:
    JsonBuilderPrivate *d = nullptr;
};

#endif //JSON_H
