/*
 *      Copyright (C) 2011 Tobias Arrskog
 *      https://github.com/topfs2/jsd_builder
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void print_license(ifstream &in, ofstream &out)
{
  string line;

  while (getline(in, line, '\n'))
    out << line << endl;
}

void print_json(ifstream &in, ofstream &out)
{
  string line;

  while (getline(in, line, '\n'))
  {
    out << endl << "  \"";
    for (string::iterator itr = line.begin(); itr != line.end(); itr++)
    {
      if (*itr == '"')
        out << '\\';
      out << (*itr);
    }
    out << '"';
  }

  out << ";" << endl;
}

void print_usage(const char *application)
{
  cout << application << " [license] [service_description.json] [notification_description.json]" << endl;
}

int main(int argc, char* argv[])
{
  if (argc < 4)
    print_usage(argv[0]);

  ofstream out ("ServiceDescription.h", ofstream::binary);

  ifstream license(argv[1], ios_base::in);
  ifstream service_description(argv[2], ios_base::in);
  ifstream notification_description(argv[3], ios_base::in);

  if (!(license && service_description && notification_description))
  {
    cout << "Failed to find one or more of license, service_description.json or notification_description.json" << endl;
    return -1;
  }

  out << "#pragma once" << endl;

  print_license(license, out);

  out << endl;

  out << "namespace JSONRPC" << endl;
  out << "{" << endl;

  out << "  const char* const JSON_SERVICE_DESCRIPTION = ";
  print_json(service_description, out);

  out << endl;

  out << "  const char* const JSON_NOTIFICATION_DESCRIPTION =";
  print_json(notification_description, out);

  out << "}" << endl;

  return 0;
}
