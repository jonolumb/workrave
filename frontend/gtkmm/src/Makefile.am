# Process this file with automake to produce Makefile.in
#
# Copyright (C) 2001, 2002, 2003, 2004 Rob Caelers & Raymond Penners
#
# $Id$
#

SUBDIRS = 		gnome_applet win32
MAINTAINERCLEANFILES = 	Makefile.in ${IDL_A_GENERATED} ${IDL_C_GENERATED}


bin_PROGRAMS = 		workrave

IDL_A = 		gnome_applet/Workrave-Applet.idl

IDL_A_GENERATED = 	Workrave-Applet.h			\
			Workrave-Applet-common.c		\
			Workrave-Applet-skels.c			\
			Workrave-Applet-stubs.c

IDL_C = 		gnome_applet/Workrave-Control.idl

IDL_C_GENERATED = 	Workrave-Control.h			\
			Workrave-Control-common.c		\
		  	Workrave-Control-skels.c		\
			Workrave-Control-stubs.c

DEFS = 			@DEFS@ -DGNOMELOCALEDIR=\""$(datadir)/locale"\" \
			-I$(top_srcdir)/intl -I..

if HAVE_APP_GTKMM

if HAVE_GNOME
sourcesgnome = 		RemoteControl.cc
sourcesidl = 		${IDL_C_GENERATED} ${IDL_A_GENERATED}

## CORBA stuff

$(IDL_A_GENERATED): $(IDL_A) 
	$(ORBIT_IDL) -I $(srcdir) -I $(datadir)/idl $(IDL_INCLUDES) \
		gnome_applet/Workrave-Applet.idl

$(IDL_C_GENERATED): $(IDL_C) 
	$(ORBIT_IDL) -I $(srcdir) -I $(datadir)/idl $(IDL_INCLUDES) \
		gnome_applet/Workrave-Control.idl

## End CORBA stuff
else
sourcesgnome = 		gnome-about.c
endif

if HAVE_X
sourcesx = 		AppletWindow.cc eggtrayicon.c
endif

if PLATFORM_WIN32
sourceswin32 = 		resource.rc
includeswin32 = 	-I$(top_srcdir)/common/win32/harpoon/include -Iwin32/ \
			-I../../win32/applet/include
workrave_LDFLAGS = 	-Lwin32/
endif

DISTRIBUTION_HOME = 	../../plugin/distribution
if HAVE_DISTRIBUTION
sourcesdistribution = 	${DISTRIBUTION_HOME}/gtkmm/src/NetworkJoinDialog.cc \
			${DISTRIBUTION_HOME}/gtkmm/src/NetworkLogDialog.cc \
			${DISTRIBUTION_HOME}/gtkmm/src/NetworkPreferencePage.cc
endif

EXERCISES_HOME =	../../plugin/exercises
if HAVE_EXERCISES
sourcesexercises = 	${EXERCISES_HOME}/gtkmm/src/ExercisesDialog.cc \
			${EXERCISES_HOME}/gtkmm/src/ExercisesPanel.cc \
			${EXERCISES_HOME}/common/src/Exercise.cc
endif

STATISTICS_HOME = 	../../plugin/statistics

if PLATFORM_WIN32
WINDRES ?= 		"windres"
.rc.o:
	${WINDRES} -o $@ $<

includesinput = 	-I$(top_srcdir)/common/win32/harpoon/include
WIN32LIBS = 		$(top_srcdir)/common/win32/harpoon/src/Release/harpoon.lib \
			-lworkrave-frontend-gtkmm-win32 \
			-lshell32 -lole32 -lwinmm
endif

if HAVE_X
X11LIBS = 		-lXmu
endif

workrave_SOURCES = \
			$(sourcesidl) \
			BreakWindow.cc \
			DailyLimitWindow.cc \
			GUI.cc \
			GtkUtil.cc \
			EventLabel.cc \
			HeadInfo.cc \
			Hig.cc \
			IconListNotebook.cc \
			IconListCellRenderer.cc \
			MainWindow.cc \
			MicroPauseWindow.cc \
			PreferencesDialog.cc \
			PreludeWindow.cc \
			RestBreakWindow.cc \
			${STATISTICS_HOME}/gtkmm/src/StatisticsDialog.cc \
			TimeBar.cc \
			TimeEntry.cc \
			TimerPreferencesPanel.cc \
			WindowHints.cc \
			gnome-winhints.c \
			Frame.cc \
			WmSpec.cc \
			TimerBoxGtkView.cc \
			TimerBoxPreferencePage.cc \
			Menus.cc \
			Dispatcher.cc \
			main.cc \
			$(sourcesgnome) \
			$(sourcesx) \
			$(sourceswin32) \
			${sourcesdistribution} \
			${sourcesexercises}

workrave_CXXFLAGS = 	-DWORKRAVE_DATADIR="\"${pkgdatadir}\"" -W \
			@WR_FRONTEND_CFLAGS@ -I$(top_srcdir)/src \
			 -I. @GNOMEUIMM_CFLAGS@ \
			@GNOMEUI_CFLAGS@ @GTK_CFLAGS@ @GTKMM_CFLAGS@ \
			@GCONF_CFLAGS@ -D_XOPEN_SOURCE=600 @GNET_CFLAGS@ \
			$(includeswin32) $(includesinput) \
			-I${DISTRIBUTION_HOME}/gtkmm/src \
			-I${STATISTICS_HOME}/gtkmm/src \
			-I${EXERCISES_HOME}/gtkmm/src \
			-I${EXERCISES_HOME}/common/src 

workrave_CFLAGS	= 	-DWORKRAVE_DATADIR="\"${pkgdatadir}\"" \
			@WR_FRONTEND_CFLAGS@ -I$(top_srcdir)/src \
			-I. @GNOMEUI_CFLAGS@ \
			@GTK_CFLAGS@ @GTKMM_CFLAGS@ -D_XOPEN_SOURCE=600 \
			-I${DISTRIBUTION_HOME}/gtkmm/src \
			-I${STATISTICS_HOME}/gtkmm/src \
			-I${EXERCISES_HOME}/gtkmm/src \
			-I${EXERCISES_HOME}/common/src 

endif

$(bin_PROGRAMS): @WR_FRONTEND_LIBS@

workrave_LDADD =  	@WR_FRONTEND_LIBS@ @GNOMEUI_LIBS@ @GNOMEUIMM_LIBS@ \
			@GTK_LIBS@ @GTKMM_LIBS@ @GNET_LIBS@ @GTHREAD_LIBS@ \
			@PTHREAD_LIBS@ @X_LIBS@ @GCONF_LIBS@ @GDOME_LIB@ \
			${X11LIBS} ${WIN32LIBS} ${WIN32CONSOLE}

# workrave_LINK		= $(LINK) \
# 			  nm - nos > workrave.dmp \
# 			  strip workrave$(EXEEXT)

#workrave$(EXEEXT): $(workrave_OBJECTS) $(workrave_DEPENDENCIES) 
#	@rm -f workrave$(EXEEXT)
#	$(CXXLINK) $(workrave_LDFLAGS) $(workrave_OBJECTS) $(workrave_LDADD) $(LIBS)

EXTRA_DIST = 		$(wildcard *.hh) $(wildcard *.cc) $(wildcard *.c) \
			$(wildcard *.h)  $(wildcard *.icc)