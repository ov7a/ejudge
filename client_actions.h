/* -*- c -*- */
/* $Id$ */

#ifndef __CLIENT_ACTIONS_H__
#define __CLIENT_ACTIONS_H__

/* Copyright (C) 2002 Alexander Chernov <cher@ispras.ru> */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

enum
  {
    ACTION_DUMMY = 0,
    ACTION_RUN_CHANGE_USER_ID,
    ACTION_RUN_CHANGE_USER_LOGIN,
    ACTION_RUN_CHANGE_LANG,
    ACTION_RUN_CHANGE_PROB,
    ACTION_RUN_CHANGE_STATUS,
    ACTION_USER_TOGGLE_BAN,
    ACTION_USER_TOGGLE_VISIBILITY,
    ACTION_GENERATE_PASSWORDS_1,
    ACTION_GENERATE_PASSWORDS_2,
    ACTION_SUSPEND,
    ACTION_RESUME,
    ACTION_UPDATE_STANDINGS_1,
    ACTION_UPDATE_STANDINGS_2,
    ACTION_RESET_1,
    ACTION_RESET_2,
    ACTION_START,
    ACTION_STOP,
    ACTION_REJUDGE_ALL_1,
    ACTION_REJUDGE_ALL_2,
    ACTION_REJUDGE_PROBLEM,
    ACTION_SCHEDULE,
    ACTION_DURATION,
    ACTION_LOGOUT,
    ACTION_CHANGE_LANGUAGE,
    ACTION_CHANGE_PASSWORD,
    ACTION_SUBMIT_RUN,
    ACTION_SUBMIT_CLAR,
    ACTION_LAST
  };

#endif /* __CLIENT_ACTIONS_H__ */

